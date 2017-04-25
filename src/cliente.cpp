#include <iostream>

int main(int argc, char *argv[]) {
    /* check num. of arguments recieved */
    if (argc < 4){
        std::cerr<<"Invalid number of arguments"<<std::endl;
        return 0;
    }

    /* retrieve information from arguments */
    std::string serverIP = argv[1];
    std::string portToConnect = argv[2];
    std::string execMode = argv[3];
    std::string userID;

    /* if user is not admin, get its user ID */
    if (execMode != "admin"){
        userID = argv[4];
    }
}