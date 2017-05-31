#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include "server.h"
#include "serverSocket.h"
#include "commonTPException.h"
#include "serverThread.h"
#include "serverQuitThread.h"
#include "serverClientThread.h"
#include <list>

#define SUCCESSRETURNVALUE 0

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

    serverMonitor serverMonitor1(server);

    ServerSocket serverSocket(port);
    serverSocket.socket_listen();

    /* vector with client threads */
    std::list<ClientThread> clientThreads;

    /* bool to check if q was entered in server1.
     * According to the statement, all activities should be terminated
     * when the server1 receives a 'q' from input
     * */
    bool haveToQuit = false;
    /* thread checking for q input in server1 */
    QuitThread quitThread(haveToQuit, serverSocket);
    quitThread.start();

    try {
        while (!haveToQuit){
            /* first remove inactive threads */
            for (auto it = clientThreads.begin(); it != clientThreads.end();
                 ++it){
                if (it->isErasable()){
                    it->join();
                    it = clientThreads.erase(it);
                }
            }

            ServerSocket acceptedSocket = serverSocket.socket_accept();
            clientThreads.emplace_back(acceptedSocket,
                                       serverMonitor1, haveToQuit);
            clientThreads.back().start();
        }
    }catch (const TPException &e){}

    quitThread.join();
    for (auto it = clientThreads.begin(); it != clientThreads.end(); ++it){
        (*it).join();
    }
    clientThreads.clear();

    serverSocket.socket_close();
    return SUCCESSRETURNVALUE;
}
