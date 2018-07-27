#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include "../Listener/listener.hpp"

int main(int argc, const char** argv) {
    Listener l;
    l.engageConnection();
    if (l.isConnectionEstablished())
        l.listen();

    getchar();
    shutdown(l.getSocket(), SHUT_RDWR);
}