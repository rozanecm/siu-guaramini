#ifndef SIU_GUARAMINI_SERVERSOCKET_H
#define SIU_GUARAMINI_SERVERSOCKET_H


#include "commonSocket.h"
#include "clientSocket.h"

class ServerSocket : public commonSocket {
public:
    explicit ServerSocket(const char *port);

    void socket_listen();

    ServerSocket socket_accept();

    void socket_shutdown();

private:
    explicit ServerSocket(int fd);
};


#endif //SIU_GUARAMINI_SERVERSOCKET_H
