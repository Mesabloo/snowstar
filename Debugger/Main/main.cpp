#include <iostream>

#include <termcolor.hpp>
#include <Listener/listener.hpp>

int main(/* int argc, const char** argv */) {
    Listener l;
    l.engageConnection();
    if (l.isConnectionEstablished())
        l.listen();

    std::cerr << termcolor::yellow << "Debugger process terminated with code " << shutdown(l.getSocket(), SHUT_RDWR) << ": ";
    perror("");
    std::cerr << termcolor::reset << std::endl;
    getchar();
}