#include <netdb.h>
#include <string>
#include <unistd.h>
#include <cstring>
#include "clientSocket.h"
#include "commonTPException.h"

clientSocket::clientSocket(const char *serverIP,
                                             const char *port) {
    const char * node = serverIP;
    const char * service = port;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *result, *rp;

    int g = getaddrinfo(node, service, &hints, &result);
    /*Error check*/
    if (g != 0){
        throw TPException(std::string("Error in client socket creation. "
                                              "getaddrinfo: ") +
                                  gai_strerror(g));
    }else{
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
            if (connect(fd, rp->ai_addr, rp->ai_addrlen) != -1){
                break;
            }
            /*if everything fails...*/
            close(fd);
            throw TPException(std::string("Error en la creacion/conexion del "
                                                  "socket cliente."));
        }
    }
    freeaddrinfo(result);
}
