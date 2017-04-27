#include <iostream>
#include <map>
#include <fstream>
#include "serverUser.h"
#include "serverSubject.h"
#include "server.h"

void freeUsers(std::map<int, User *> &users);

int main(int argc, char *argv[]) {
    /* check num. of arguments received */
//    if (argc != 4){
//        std::cerr<<"Invalid number of arguments"<<std::endl;
//        return 0;
//    }
    server server;

    /* retrieve information from arguments*/
    std::string port = argv[1];
    std::string usersFilepath = argv[1];
    std::string subjectsFilepath = argv[2];

    /* store file information */
    server.processUsersFile(usersFilepath);
    server.processSubjectsFile(subjectsFilepath);

    return 0;
}

