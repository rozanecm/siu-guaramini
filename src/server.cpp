int main(int argc, char *argv[]) {
    /* check num. of arguments recieved */
    if (argc != 4){
        std::cerr<<"Invalid number of arguments"<<std::endl;
        return 0;
    }

    /* retrieve information from arguments*/
    int port = argv[1];
    std::string usersFilepath = argv[2];
    std::string subjectsFilepath = argv[3];


}