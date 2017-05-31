#include "serverClientThread.h"
#include "commonProtocoler.h"
#include <string>
#include <netinet/in.h>

ClientThread::ClientThread(ServerSocket serverSocket1, serverMonitor &server,
                           bool &quit) :
        serverSocket(serverSocket1), server(server), quit(quit) {
    erasable = false;
}

void ClientThread::run() {
    bool socketWasClosed = false;
    std::string clientData = commonProtocoler::recv(serverSocket,
                                                    socketWasClosed);
    /* from the client data, get what type of user just connected */
    clientData = clientData.substr(0, clientData.find_first_of("\f"));
    std::string userType =
            clientData.substr(0, clientData.find_first_of(" "));
    clientData.erase(0, clientData.find_first_of(" ") + 1);
    std::string userIDstring = "";

    if (userType != "admin") {
        /* if it is not admin, get its id */
        userIDstring = clientData;
    }

    if (!server.validateClientData(userType, userIDstring)){
        serverSocket.socket_close();
        socketWasClosed = true;
        /* inform disconnect */
        server.informDisconnect(userType, userIDstring);
    }

    while (!socketWasClosed && !quit){
        /* get msg from client */
        std::string receivedMsg = commonProtocoler::recv(serverSocket,
                                                         socketWasClosed);
        if (socketWasClosed)
            break;
        /* retrieve commmand from msg */
        std::string command = receivedMsg.substr(0, 2);
        receivedMsg.erase(0, 3);

        /* process command */
        if (command == "lm"){
            /* command code: lm -> listar materias */
            server.informReceivedCommand(userType, userIDstring, "lm");
            std::string msgToSend = server.listSubjects();

            commonProtocoler::send(serverSocket, msgToSend);
        }else if (command == "li"){
            /* command code: li -> listar inscripciones */
            server.informReceivedCommand(userType, userIDstring, "li");
            std::string msgToSend = server.
                    listEnrollments(userType, std::stoi(userIDstring));

            commonProtocoler::send(serverSocket, msgToSend);
        }else if (command == "in"){
            /* command code: in -> inscribirse */
            server.informReceivedCommand(userType, userIDstring, "in");

            int idAlumno, codigoMateria, codigoCurso;
            std::string msgForClient = "";

            /* get data from input */
            getDataFromInputForEnrollOrUnenrollCommand(receivedMsg, userType,
                                             userIDstring, idAlumno,
                                             codigoMateria, codigoCurso);
            /* proceed to enrollment */
            if (userType == "docente"){
                msgForClient = server.enroll(idAlumno, codigoMateria,
                                             codigoCurso,
                                             std::stoi(userIDstring));
            } else{
                msgForClient = server.enroll(idAlumno, codigoMateria,
                                             codigoCurso);
            }

            commonProtocoler::send(serverSocket, msgForClient);
        }else if (command == "de"){
            /* command code: de -> desinscribirse */
            server.informReceivedCommand(userType, userIDstring, "de");

            int idAlumno, codigoMateria, codigoCurso;
            std::string msgForClient = "";

            /* get data from input */
            getDataFromInputForEnrollOrUnenrollCommand(receivedMsg, userType,
                                                       userIDstring, idAlumno,
                                                       codigoMateria,
                                                       codigoCurso);

            /* proceed to unEnrollment */
            if (userType == "docente"){
                msgForClient = server.unEnroll(idAlumno, codigoMateria,
                                               codigoCurso,
                                               std::stoi(userIDstring));
            } else{
                msgForClient = server.unEnroll(idAlumno, codigoMateria,
                                               codigoCurso);
            }
            commonProtocoler::send(serverSocket, msgForClient);
        }
    }
    serverSocket.socket_close();
    erasable = true;
    /* inform disconnect */
    server.informDisconnect(userType, userIDstring);
}

void ClientThread::getDataFromInputForEnrollOrUnenrollCommand(
        std::string &receivedMsg,
        const std::string &userType,
        const std::string &userIDstring,
        int &idAlumno,
        int &codigoMateria,
        int &codigoCurso) {
    if (userType == "alumno"){
        /* get codigo materia */
        codigoMateria = std::stoi(receivedMsg.substr(0, receivedMsg.find(' ')));
        receivedMsg.erase(0, receivedMsg.find(' ') + 1);

        /* get codigo curso */
        codigoCurso = std::stoi(receivedMsg);

        /* set id alumno */
        idAlumno = std::stoi(userIDstring);
    }else{
        /* get id alumno */
        idAlumno = std::stoi(receivedMsg.substr(0, receivedMsg.find(' ')));
        receivedMsg.erase(0, receivedMsg.find(' ') + 1);

        /* get codigo materia */
        codigoMateria = std::stoi(receivedMsg.substr(0, receivedMsg.find(' ')));
        receivedMsg.erase(0, receivedMsg.find(' ') + 1);

        /* get codigo curso */
        codigoCurso = std::stoi(receivedMsg);
    }
}

bool ClientThread::isErasable() {
    return this->erasable;
}
