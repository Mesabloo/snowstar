#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

class Listener {
    public:
        Listener();
        ~Listener();

        void engageConnection();
        void listen();

        bool isConnectionEstablished() const;

        int getSocket() const;

    private:
        bool interpret(char* const);

    protected:
        int m_socket, m_port;
        sockaddr_in sock_addr;
        bool conn_ok;
};

#endif