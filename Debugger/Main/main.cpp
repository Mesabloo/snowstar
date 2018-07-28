#include <iostream>

#include "../../Common/termcolor.hpp"
#include "../Listener/listener.hpp"

int main(/* int argc, const char** argv */) {
    Listener l;
    l.engageConnection();
    if (l.isConnectionEstablished())
        l.listen();

    std::cerr << shutdown(l.getSocket(), SHUT_RDWR) << ": ";
    perror("");
    std::cerr << termcolor::reset << std::endl;
}