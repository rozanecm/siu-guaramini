#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include "serverUser.h"
#include "server.h"
#include "serverSocket.h"
#include "commonTPException.h"
#include "serverThread.h"

#define SUCCESSRETURNVALUE 0

void freeUsers(std::map<int, User *> &users);

int main(int argc, char *argv[]) {
    /* check num. of arguments received */
    if (argc != 4){
        throw TPException(std::string("Invalid number of arguments"));
    }
    server server;

    /* retrieve information from arguments */
    const char *port = argv[1];
    std::string usersFilepath = argv[2];
    std::string subjectsFilepath = argv[3];

    /* store file information */
    server.processUsersFile(usersFilepath);
    server.processSubjectsFile(subjectsFilepath);

    ServerSocket serverSocket(port);
    serverSocket.socket_listen();

    std::vector<Thread> threads;

    while(true){
        ServerSocket serverSocket1 = serverSocket.socket_accept();
        bool socketWasClosed = false;
        std::string clientData =  serverSocket1.socket_recv(socketWasClosed);
        /* from the client data, get what type of user just connected */
        clientData = clientData.substr(0, clientData.find_first_of("\f"));
        std::string userType =
                clientData.substr(0, clientData.find_first_of(" "));
        std::string userIDstring;

        if (userType != "admin") {
            /* if it is not admin, get its id */
            userIDstring = clientData.substr(clientData.find_first_of(" ") + 1);
        }

        if (!server.validateClientData(userType, userIDstring)){
            serverSocket1.socket_close();
            socketWasClosed = true;
            /* inform disconnect */
            server.informDisconnect(userType, userIDstring);
        }

        while(!socketWasClosed){
            /* get msg from client */
            std::string receivedMsg = serverSocket1.
                    socket_recv(socketWasClosed);

            /* retrieve commmand from msg */
            std::string command = receivedMsg.substr(0, 2);
            receivedMsg.erase(0, 3);

            /* process command */
            if (command == "lm"){
                /* command code: lm -> listar materias */
                server.informReceivedCommand(userType, userIDstring, "lm");
                std::string msgToSend = server.listSubjects();
                serverSocket1.socket_send(msgToSend);
            }else if (command == "li"){
                /* command code: li -> listar inscripciones */
                server.informReceivedCommand(userType, userIDstring, "li");
                std::string msgToSend = server.
                        listEnrollments(userType, std::stoi(userIDstring));
                serverSocket1.socket_send(msgToSend);
            }else if (command == "in"){
                /* command code: in -> inscribirse */
                server.informReceivedCommand(userType, userIDstring, "in");

                std::string idAlumno, codigoMateria, codigoCurso;
                std::string msgForClient;

                /* get data from input */
                if (userType == "alumno"){
                    /* get codigo materia */
                    codigoMateria = receivedMsg.
                            substr(0, receivedMsg.find(' '));
                    receivedMsg.erase(0, receivedMsg.find(' ') + 1);

                    /* get codigo curso */
                    codigoCurso = receivedMsg;

                    /* set id alumno */
                    idAlumno = userIDstring;
                }else{
                    /* get id alumno */
                    idAlumno = receivedMsg.substr(0, receivedMsg.find(' '));
                    receivedMsg.erase(0, receivedMsg.find(' ') + 1);

                    /* get codigo materia */
                    codigoMateria = receivedMsg.
                            substr(0, receivedMsg.find(' '));
                    receivedMsg.erase(0, receivedMsg.find(' ') + 1);

                    /* get codigo curso */
                    codigoCurso = receivedMsg;
                }
                /* proceed to enrollment */
                if (userType == "docente"){
                    msgForClient = server.enroll(std::stoi(idAlumno),
                                                 std::stoi(codigoMateria),
                                                 std::stoi(codigoCurso),
                                                 std::stoi(userIDstring));
                } else{
                    msgForClient = server.enroll(std::stoi(idAlumno),
                                                 std::stoi(codigoMateria),
                                                 std::stoi(codigoCurso));
                }
                serverSocket1.socket_send(msgForClient);
            }else if (command == "de"){
                /* command code: de -> desinscribirse */
                server.informReceivedCommand(userType, userIDstring, "de");

                std::string idAlumno, codigoMateria, codigoCurso;
                std::string msgForClient;

                /* get data from input */
                if (userType == "alumno"){
                    /* get codigo materia */
                    codigoMateria = receivedMsg.
                            substr(0, receivedMsg.find(' '));
                    receivedMsg.erase(0, receivedMsg.find(' ') + 1);

                    /* get codigo curso */
                    codigoCurso = receivedMsg;

                    /* set id alumno */
                    idAlumno = userIDstring;
                }else{
                    /* get id alumno */
                    idAlumno = receivedMsg.substr(0, receivedMsg.find(' '));
                    receivedMsg.erase(0, receivedMsg.find(' ') + 1);

                    /* get codigo materia */
                    codigoMateria = receivedMsg.
                            substr(0, receivedMsg.find(' '));
                    receivedMsg.erase(0, receivedMsg.find(' ') + 1);

                    /* get codigo curso */
                    codigoCurso = receivedMsg;
                }
                /* proceed to enrollment */
                if (userType == "docente"){
                    msgForClient = server.unEnroll(std::stoi(idAlumno),
                                                 std::stoi(codigoMateria),
                                                 std::stoi(codigoCurso),
                                                 std::stoi(userIDstring));
                } else{
                    msgForClient = server.unEnroll(std::stoi(idAlumno),
                                                 std::stoi(codigoMateria),
                                                 std::stoi(codigoCurso));
                }
                serverSocket1.socket_send(msgForClient);
            }
        }
        break;
    }


    return SUCCESSRETURNVALUE;
}
