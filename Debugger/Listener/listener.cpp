#include <iostream>
#include <iomanip>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <termcolor.hpp>
#include <Utils/utils.hpp>

#include "listener.hpp"

Listener::Listener(): m_port{9999}, conn_ok{false} {
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0) {
        std::cerr << termcolor::red << "An error occurred while opening a socket." << '\n'
            << "What happened: ";
        perror("");
        std::cerr << termcolor::reset << std::endl;
        return;
    }
    bzero(reinterpret_cast<sockaddr_in*>(&sock_addr), sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sock_addr.sin_port = htons(m_port);
}
Listener::~Listener() {}

void Listener::engageConnection() {
    if (connect(m_socket, reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr)) == 0) {
        char buf[10];
        char send[10] = {'h', 'e', 'a', 'r', 't', 'b', 'e', 'a', 't', '\0'};
        write(m_socket, send, 10);
        read(m_socket, buf, 10);
        if (std::string{buf, 9} == "heartbeat")
            conn_ok = true;
        else
            conn_ok = false;
    } else {
        std::cerr << termcolor::red << "An error occured while connecting. Is the server running ?" << '\n'
            << "What happened: ";
        perror("");
        std::cerr << termcolor::reset << std::endl;
        return;
    }
    if (!isConnectionEstablished()) return;
    std::clog << termcolor::green << "Successfully attached to the VM." << termcolor::reset << std::endl;
}

bool valid = true;
void Listener::listen() {
    while (true) {
        if (valid) {
            char buf[4096];
            read(m_socket, buf, 4096);
            uint16_t size = static_cast<uint16_t>(buf[0]);
            // std::clog << "Official size (first byte in packet)=" << std::to_string(size) << " // Real size (strlen)=" << std::to_string(strlen(buf)-1) << std::endl;
            int i;
            // std::clog << termcolor::grey << "Packet_buffer=" << buf << termcolor::reset << std::endl;
            if (buf[0] == 'e' && buf[1] == 'r' && buf[2] == 'r' && buf[3] == 'o' && buf[4] == 'r') {
                size = 4096;
                i = 0;
            } else {
                i = 1;
            }
            std::string cmd;
            // std::clog << "Packet='" << buf << "'";
            while (buf[i] != '\0' && i <= size) {
                cmd += buf[i];
                i++;
            }
            //std::clog << "Command received='" << cmd << "'" << std::endl;
            if (!interpret(cmd))
                break;
        } else
            valid = true;
        std::cout << termcolor::blue << ">> ";
        std::string line{""};
        getline(std::cin, line);
        if (line == "") {
            valid = false;
            continue;
        }
        std::cout << termcolor::reset;
        std::cout.flush();
        if (!check(line)) {
            std::cerr << termcolor::red << "Invalid use of command or inexistant command." << termcolor::reset << std::endl;
            valid = false;
            continue;
        }
        char const size = static_cast<char>(line.size());
        char tmp[256];
        tmp[0] = size;
        for (size_t i{0};i < line.size();++i) {
            if (i > 255) break;
            tmp[i+1] = line[i];
        }
        char const null[1] = {'\0'};
        for (int length{size+1};length < 256;++length)
            strcat(tmp, null);
        write(m_socket, tmp, strlen(tmp));
    }
}

bool Listener::interpret(std::string const& buffer) const {
    if (buffer == "") return true;
    std::vector<std::string> splitted = utils::str_split(buffer, ' ');
    if (splitted[0] == "exit") {
        std::clog << termcolor::cyan << "Received exit command from VM." << termcolor::reset << std::endl;
        return false; 
    }
    if (splitted[0] == "stats") {
        std::clog << termcolor::magenta;
        std::string arguments{""};
        for (size_t i{1};i < splitted.size();++i) {
            if (i == 1)
                arguments = splitted[i];
            else
                arguments = utils::str_join(arguments, splitted[i], ' ');
        }
        // std::clog << termcolor::red << arguments << termcolor::reset << std::endl;
        std::vector<std::string> args = utils::str_split(arguments, '\n');
        // mem = args[0]
        {
            std::vector<std::string> stats = utils::str_split(args[0], '=');
            stats = utils::str_split(stats[1], ';');
            float max_size = static_cast<float>(std::stoi(stats[0])),
                size{0};
            if (stats[1] != "empty")
                size = static_cast<float>(std::stoi(stats[1]));
            std::clog << "-> Memory: { " << "Max size=" << max_size << ", Used size=" << size << ", Percentage of the memory=" << std::setprecision(3) << (size*100/max_size) << "% }" << std::endl;
        }
        // temp = args[1]
        {
            std::vector<std::string> stats = utils::str_split(args[1], '=');
            stats = utils::str_split(stats[1], ';');
            float max_size = static_cast<float>(std::stoi(stats[0])),
                size{0};
            if (stats[1] != "empty")
                size = static_cast<float>(std::stoi(stats[1]));
            std::clog << "-> Temporary: { " << "Max size=" << max_size << ", Used size=" << size << ", Percentage of the memory=" << std::setprecision(3) << (size*100/max_size) << "% }" << std::endl;
        }
        // param = args[2]
        {
            std::vector<std::string> stats = utils::str_split(args[2], '=');
            float size{0};
            if (stats[1] != "empty")
                size = static_cast<float>(std::stoi(stats[1]));
            std::clog << "-> Parameters: { Size=" << size << " }" << std::endl;
        }
        // current instruction = args[3]+args[4...]
        std::string consumer{args[3]};
        for (size_t i{4};i < args.size();++i)
            consumer = utils::str_join(consumer, 'n'+args[i], '\\');
        std::clog << "-> Current line: " << consumer;
        std::clog << termcolor::reset << std::endl;
        return true;
    }
    if (splitted[0] == "error") {
        std::string error{splitted[1]};
        for (size_t i{2};i < splitted.size();++i)
            error = utils::str_join(error, splitted[i], ' ');
        std::clog << termcolor::red << "/!\\\t" << error << termcolor::reset << std::endl;
        return false;
    }
    return true;
}

bool Listener::check(std::string const& cmd) const {
    std::vector<std::string> splitted{utils::str_split(cmd, ' ')};
    if (splitted[0] == "exec") {
        if (splitted.size() != 2) return false;
        if (!utils::str_is_number(splitted[1])) return false;
        return true;
    }
    if (splitted[0] == "exit")
        return true;
    return false;
}

bool Listener::isConnectionEstablished() const { return conn_ok; }
int Listener::getSocket() const { return m_socket; }