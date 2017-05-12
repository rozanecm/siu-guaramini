#include <netinet/in.h>
#include "commonProtocoler.h"

#define BYTESFORLENGTHOFMESSAGE 4

void commonProtocoler::send(commonSocket &socket, const std::string &message) {
    /* first send msg length */
    unsigned long msgSize = message.size();
    uint32_t netLenMsgSize = htonl(msgSize);
    socket.socket_send((char *) &netLenMsgSize, BYTESFORLENGTHOFMESSAGE);
    /* send actual msg */
    socket.socket_send(message.c_str(), msgSize);
}

std::string
commonProtocoler::recv(commonSocket &socket, bool &socketWasShutDown) {
    /* first get msg's length */
    size_t messageToReadLength;
    socket.socket_recv(socketWasShutDown, BYTESFORLENGTHOFMESSAGE, (char*)&messageToReadLength);
    if (socketWasShutDown)
        return "";
    messageToReadLength = ntohl(messageToReadLength);
    /* get actual msg */
    char msgFromServerChar[500] = "";
    socket.socket_recv(socketWasShutDown, messageToReadLength, msgFromServerChar);
    std::string msgReceived(msgFromServerChar);
    return msgReceived;
}
