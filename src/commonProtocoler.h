#ifndef SIU_GUARAMINI_COMMONPROTOCOLER_H
#define SIU_GUARAMINI_COMMONPROTOCOLER_H


#include "commonSocket.h"

class commonProtocoler {
public:
    static void send(commonSocket &socket, const std::string &message);

    static std::string recv(commonSocket &socket, bool &socketWasShutDown);
};


#endif //SIU_GUARAMINI_COMMONPROTOCOLER_H
