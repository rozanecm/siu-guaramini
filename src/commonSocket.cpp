#include <sys/socket.h>
#include <string>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include "commonSocket.h"
#include "commonTPException.h"

void commonSocket::socket_send(std::string &messageToSend) {
    size_t messageLength = messageToSend.size();
    uint32_t nlength = htonl(messageLength);

    sendLength(nlength);
    size_t totalSentAmount = 0;
    ssize_t lastSentAmount = send(fd, messageToSend.c_str(), messageLength,
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

void commonSocket::sendLength(const size_t &lengthToSend) {
    size_t messageLength = 4;
    size_t totalSentAmount = 0;
    ssize_t lastSentAmount = send(fd, &lengthToSend, messageLength,
                                  MSG_NOSIGNAL);
    totalSentAmount += lastSentAmount;
    while (totalSentAmount < messageLength) {
        if (lastSentAmount == -1) {
            int errorNum = errno;
            throw TPException(std::string("Error en el send: ") +
                              strerror(errorNum));
        }
        totalSentAmount += lastSentAmount;
        lastSentAmount = send(fd, &lengthToSend + totalSentAmount,
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

std::string commonSocket::socket_recv(bool &socketShutDown) {
    //todo arreglar nro. magico.
    char messageToRecieve[500];
    size_t messageToReadLength = getLengthOfMsgToRead();
    if (messageToReadLength == 0){
        socketShutDown = true;
    }
    size_t totalRecievedAmount = 0;
    ssize_t lastRecievedAmount = 0;
    while (totalRecievedAmount < messageToReadLength && !socketShutDown){
        lastRecievedAmount = recv(fd, &messageToRecieve[totalRecievedAmount],
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
    std::string asdf = std::string(&messageToRecieve[0],
                                  &messageToRecieve[messageToReadLength]);
    return asdf;
}

size_t commonSocket::getLengthOfMsgToRead() {
    size_t lengthToRecieve = 0;
    bool socketShutDown = false;
    size_t totalRecievedAmount = 0;
    ssize_t lastRecievedAmount = 0;
    while (totalRecievedAmount < 4 && !socketShutDown){
        /* aka until socket is not shut down */
        lastRecievedAmount = recv(fd, ((char*)&lengthToRecieve) +
                                          totalRecievedAmount,
                                  4 - totalRecievedAmount,
                                  MSG_NOSIGNAL);
        /* ERROR CHECK */
        if (lastRecievedAmount == -1){
            int error = errno;
            throw TPException(std::string("Error en el recieve: ") +
                              strerror(error));
        } else if (lastRecievedAmount == 0) {
            /* socket was shut down */
            socketShutDown = true;
        } else {
            totalRecievedAmount += lastRecievedAmount;
        }
    }
    return ntohl(lengthToRecieve);
}
