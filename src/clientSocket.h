#ifndef SIU_GUARAMINI_CLIENTSOCKET_H
#define SIU_GUARAMINI_CLIENTSOCKET_H


#include "commonSocket.h"

class clientSocket : public commonSocket {
public:
    clientSocket (const char *serverIP, const char *port);
};


#endif //SIU_GUARAMINI_CLIENTSOCKET_H
