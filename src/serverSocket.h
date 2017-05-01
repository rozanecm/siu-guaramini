#ifndef SIU_GUARAMINI_SERVERSOCKET_H
#define SIU_GUARAMINI_SERVERSOCKET_H


#include "commonSocket.h"
#include "clientSocket.h"

class ServerSocket : public commonSocket {
public:
    ServerSocket(int fd);

    ServerSocket(const char *port);

    void socket_listen();

    ServerSocket socket_accept();
};


#endif //SIU_GUARAMINI_SERVERSOCKET_H
