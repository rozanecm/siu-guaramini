#include <netdb.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include "serverSocket.h"
#include "commonTPException.h"

ServerSocket::ServerSocket(const char *port) {
    const char * service = port;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *result, *rp;

    int g = getaddrinfo(NULL, service, &hints, &result);
    /* Error check */
    if (g != 0){
        throw TPException(std::string("getaddrinfo: ") + gai_strerror(g));
    }
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        fd = socket(rp->ai_family, rp->ai_socktype,
                               rp->ai_protocol);
        /* ERROR CHECKING
         * According to documentation: "On success, a file descriptor
         * for the new socket is returned.  On error, -1 is returned,
         * and errno is set appropriately."
         * */
        if (fd == -1){
            continue;
        }
        if (bind(fd, rp->ai_addr, rp->ai_addrlen) != -1){
            break;
        }
        /* if everything fails... */
        close(fd);
        throw TPException(std::string("Error with socket creation/binding."));
    }
    freeaddrinfo(result);
}

ServerSocket::ServerSocket(int fd) {
    /* initialization list was not used because fd is from parent class */
    this->fd = fd;
}

void ServerSocket::socket_listen() {
#define BACKLOG 5
    /* The backlog argument defines the
     * maximum length to which the queue of pending connections for socket_fd
     * may grow. If a connection request arrives when the queue is full, the
     * client may receive an error with an indication of ECONNREFUSED or, if
     * the underlying protocol supports retransmission, the request may be
     * ignored so that a later reattempt at connection succeeds.
     * */
    int ret = listen(fd, BACKLOG);

    /* ERROR CHECK */
    if (ret == -1){
        int error = errno;
        throw TPException(std::string("Error with socket listen: ") +
                                  strerror(error));
    }
}

ServerSocket ServerSocket::socket_accept() {
    struct sockaddr clientSocket;
    socklen_t cliLength = sizeof(clientSocket);
    int ret = accept(fd, (struct sockaddr *)&clientSocket,
                     &cliLength);

    /* From accept man page:
     * On success, these system calls return a nonnegative integer that is a
     * descriptor for the accepted socket.  On error, -1 is returned,
     * and errno is set appropriately.
     * */

    /* ERROR CHECK */
    if (ret == -1){
        int error = errno;
        throw TPException(std::string("Error with socket accept: ") +
                                  strerror(error));
    }
    return ServerSocket(ret);
}

void ServerSocket::socket_shutdown() {
    int ret = shutdown(fd, SHUT_RDWR);

    /* ERROR CHECK */
    if (ret == -1){
        int error = errno;
        throw TPException(std::string("Error en shutdown del socket: ") +
                                  strerror(error));
    }
}
