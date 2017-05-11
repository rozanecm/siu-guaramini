#ifndef SIU_GUARAMINI_SERVERQUITTHREAD_H
#define SIU_GUARAMINI_SERVERQUITTHREAD_H


#include "serverThread.h"
#include "serverSocket.h"

class QuitThread : public Thread {
private:
    bool &quit;

    ServerSocket &serverSocket;
public:
    QuitThread(bool &quit, ServerSocket &serverSocket);

    virtual void run();
};


#endif //SIU_GUARAMINI_SERVERQUITTHREAD_H
