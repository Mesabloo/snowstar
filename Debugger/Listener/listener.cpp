#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../../Common/termcolor.hpp"
#include "../../Common/Utils/utils.hpp"

#include "listener.hpp"

Listener::Listener(): m_port{9999}, conn_ok{false} {
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0) {
        std::cerr << termcolor::red << "An error occurred while opening a socket." << '\n'
            << "What happened: ";
        perror("");
        std::cerr << termcolor::reset << std::endl;
        getchar();
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
        // Succesfully connected.
        char buf[1024];
        strncpy(buf, "heartbeat", 10);
        write(m_socket, buf, strlen(buf));
        read(m_socket, buf, 1024);
        std::cout << "Response from the server: " << buf << std::endl;
        conn_ok = true;
    } else {
        std::cerr << termcolor::red << "An error occured while connecting. Is the server running ?" << '\n'
            << "What happened: ";
        perror("");
        std::cerr << termcolor::reset << std::endl;
        getchar();
        return;
    }
}

void Listener::listen() {
    while (true) {
        char buf[4096];
        read(m_socket, buf, 4096);
        if (!interpret(buf))
            break;
        std::cout << termcolor::blue << ">> ";
        std::string line;
        getline(std::cin, line);
        if (line == "") continue;
        std::cout << termcolor::reset;
        write(m_socket, line.c_str(), 4096);
    }
}

bool Listener::interpret(char* const buffer) {
    std::string buf{buffer};
    std::cout << buf << std::endl;
    if (utils::str_startswith(buf, "exit")) {
        std::cerr << termcolor::yellow << "Debugger process terminated with code ";
        return false; 
    }
    return true;
}

bool Listener::isConnectionEstablished() const { return conn_ok; }
int Listener::getSocket() const { return m_socket; }