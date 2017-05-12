#ifndef SIU_GUARAMINI_COMMONSOCKET_H
#define SIU_GUARAMINI_COMMONSOCKET_H


#include <cstdio>
#include <string>

class commonSocket {
protected:
    int fd;

public:
    void socket_send(const char *messageToSend,
                         unsigned long messageLength);

    std::string socket_recv(bool &socketShutDown, size_t messageToReadLength,
                                char *messageToReceive);

    void socket_close();
};


#endif //SIU_GUARAMINI_COMMONSOCKET_H
