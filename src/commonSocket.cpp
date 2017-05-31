#include <sys/socket.h>
#include <string>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include "commonSocket.h"
#include "commonTPException.h"

void commonSocket::socket_send(const char *messageToSend,
                               unsigned long messageLength) {
    size_t totalSentAmount = 0;
    ssize_t lastSentAmount = send(fd, messageToSend, messageLength,
                                  MSG_NOSIGNAL);
    totalSentAmount += lastSentAmount;
    while (totalSentAmount < messageLength) {
        if (lastSentAmount == -1) {
            int errorNum = errno;
            throw TPException(std::string("Error en el send: ") +
                              strerror(errorNum));
        }
        totalSentAmount += lastSentAmount;
        lastSentAmount = send(fd, &messageToSend + totalSentAmount,
                              messageLength - totalSentAmount,
                              MSG_NOSIGNAL);
    }
}

void commonSocket::socket_close() {
    int ret = close(fd);

    /* ERROR CHECK */
    if (ret == -1){
        int error = errno;
        throw TPException(std::string("Error en el cierre del socket: ") +
                                  strerror(error));
    }
}

std::string commonSocket::socket_recv(bool &socketShutDown,
                                      size_t messageToReadLength,
                                      char *messageToReceive) {
    size_t totalRecievedAmount = 0;
    ssize_t lastRecievedAmount = 0;
    while (totalRecievedAmount < messageToReadLength && !socketShutDown){
        lastRecievedAmount = recv(fd, messageToReceive + totalRecievedAmount,
                                  messageToReadLength-totalRecievedAmount,
                                  MSG_NOSIGNAL);
        /* ERROR CHECK */
        if (lastRecievedAmount == -1){
            int error = errno;
            throw TPException(std::string("Error en el receive: ") +
                                      strerror(error));
        } else if (lastRecievedAmount == 0) {
            /* socket was shut down */
            socketShutDown = true;
        } else {
            totalRecievedAmount += lastRecievedAmount;
        }
    }
    std::string retStr = std::string(&messageToReceive[0],
                                  &messageToReceive[messageToReadLength]);
    return retStr;
}
