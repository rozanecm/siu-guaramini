#include <iostream>
#include <string>
#include <netinet/in.h>
#include "commonTPException.h"
#include "clientSocket.h"

#define BYTESFORLENGTHOFMESSAGE 4

int main(int argc, char *argv[]) {
    /* check num. of arguments recieved */
    if (argc < 4){
        throw TPException(std::string("Invalid number of arguments"));
    }

    /* retrieve information from arguments */
    const char *serverIP = argv[1];
    const char *portToConnect = argv[2];
    std::string execMode = argv[3];
    std::string userID;

    /* build string with client info for server1 */
    std::string clientInfo = execMode;

    /* if user is not admin, get its user ID */
    if (execMode != "admin"){
        userID = argv[4];

        clientInfo.append(std::string(" ") + userID);
    }

    clientSocket socket(serverIP, portToConnect);

    /* send client information to server1 */
    /* first send msg length */
    unsigned long msgSize = clientInfo.size();
    uint32_t netLenMsgSize = htonl(msgSize);
    socket.socket_send((char*)&netLenMsgSize, BYTESFORLENGTHOFMESSAGE);
    /* send actual msg */
    socket.socket_send(clientInfo.c_str(), msgSize);

    std::string input;
    while (getline(std::cin, input)){
        bool socketWasShutDown = false;
        std::string command = input.substr(0, input.find(' '));
        input.erase(0, input.find(' '));
        if (command == "listarMaterias"){
            input.insert(0, "lm");
        }else if (command == "listarInscripciones"){
            input.insert(0, "li");
        }else if (command == "inscribir"){
            input.insert(0, "in");
        }else if (command == "desinscribir"){
            input.insert(0, "de");
        }
        /* first send msg length */
        unsigned long msgSize = input.size();
        uint32_t netLenMsgSize = htonl(msgSize);
        socket.socket_send((char*)&netLenMsgSize, BYTESFORLENGTHOFMESSAGE);
        /* send actual msg */
        socket.socket_send(input.c_str(), msgSize);

        /* read msg from server */
        /* first get msg's length */
        size_t messageToReadLength;
        socket.socket_recv(socketWasShutDown, BYTESFORLENGTHOFMESSAGE,
                           (char*)&messageToReadLength);
        messageToReadLength = ntohl(messageToReadLength);
        /* get actual msg */
        std::string msgFromServer;
        socket.socket_recv(socketWasShutDown, BYTESFORLENGTHOFMESSAGE,
                           (char*)&msgFromServer);

        /* print server1 msg */
        std::cout<<msgFromServer;
    }
    socket.socket_close();
    return 0;
}
