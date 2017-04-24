int main(int argc, char *argv[]) {
    /* check num. of arguments recieved */
    if (argc < 4){
        std::cerr<<"Invalid number of arguments"<<std::endl;
        return 0;
    }

    /* retrieve information from arguments */
    int serverIP = argv[1];
    int portToConnect = argv[2];
    std::string execMode = argv[3];

    /* if user is not admin, get its user ID */
    if (execMode != 'admin'){
        int userID = argv[4];
    }
}