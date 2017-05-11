#include <iostream>
#include "serverQuitThread.h"

QuitThread::QuitThread(bool &quit, ServerSocket &serverSocket) :
        quit(quit), serverSocket(serverSocket){}

void QuitThread::run() {
    char c;
    std::cin >> c;
    while (c != 'q'){
        std::cin >> c;
    }
    quit = true;
    serverSocket.socket_shutdown();
}
