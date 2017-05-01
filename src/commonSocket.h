#ifndef SIU_GUARAMINI_COMMONSOCKET_H
#define SIU_GUARAMINI_COMMONSOCKET_H


#include <cstdio>
#include <string>

class commonSocket {
protected:
    int fd;

public:
    void socket_send(std::string &messageToSend);


    std::string socket_recv(bool &socketShutDown);

    void socket_close();

private:
    size_t getLengthOfMsgToRead();

    void sendLength(const size_t &lengthToSend);
};


#endif //SIU_GUARAMINI_COMMONSOCKET_H
