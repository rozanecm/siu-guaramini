#ifndef SIU_GUARAMINI_SERVERCLIENTTHREAD_H
#define SIU_GUARAMINI_SERVERCLIENTTHREAD_H


#include "serverThread.h"
#include "serverSocket.h"
#include "server.h"
#include "serverMonitor.h"
#include <string>

class ClientThread : public Thread {
private:
    ServerSocket serverSocket;

    serverMonitor &server;

    bool &quit;

    /* erasable indicates if the thread can be erased */
    bool erasable;

public:
    ClientThread(ServerSocket serverSocket1, serverMonitor &server, bool &quit);

    virtual void run();

    void getDataFromInputForEnrollOrUnenrollCommand(
            std::string &receivedMsg, const std::string &userType,
            const std::string &userIDstring, int &idAlumno, int &codigoMateria,
            int &codigoCurso);

    bool isErasable();
};

#endif //SIU_GUARAMINI_SERVERCLIENTTHREAD_H
