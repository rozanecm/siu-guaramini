#include <iostream>
#include <map>
#include <fstream>
#include "serverUser.h"
#include "serverSubject.h"
#include "serverTeacher.h"
#include "serverStudent.h"

void processUsersFile(std::string filePath, std::map<int, User*> &users);

void processSubjectsFile(std::string filepath,
                         std::map<std::pair<int, int>, Subject *> &subjects);

int main(int argc, char *argv[]) {
    /* check num. of arguments recieved */
//    if (argc != 4){
//        std::cerr<<"Invalid number of arguments"<<std::endl;
//        return 0;
//    }

    /* retrieve information from arguments*/
    std::string port = argv[1];
    std::string usersFilepath = argv[1];
    std::string subjectsFilepath = argv[2];

    /* build structures that will hold file data */
    std::map<int, User*> users;
    std::map<std::pair<int, int>, Subject*> subjects;

    /* store file information */
    processUsersFile(usersFilepath, users);
    processSubjectsFile(subjectsFilepath, subjects);
    return 0;
}

void processSubjectsFile(std::string filepath,
std::map<std::pair<int, int>, Subject *> &subjects) {
    std::ifstream subjectsFile;
    try {
        subjectsFile.open(filepath);
    }catch (std::ios_base::failure e){
        std::cerr<<"Error opening error file"<<std::endl;
    }
    subjectsFile.seekg(0);
    while (subjectsFile.peek() != EOF) {
        std::string description, subjectID, courseID, teacherID, vacantes;

        std::getline(subjectsFile, subjectID, '\t');
        std::getline(subjectsFile, courseID, '\t');
        std::getline(subjectsFile, description, '\t');

        std::getline(subjectsFile, teacherID, '\t');
        std::getline(subjectsFile, vacantes);

        subjects.insert(std::make_pair(std::make_pair(std::stoi(subjectID), std::stoi(courseID)),
                                       new Subject(std::stoi(teacherID),
                                                   std::stoi(vacantes),
                                                   description)));
    }
    subjectsFile.close();
}

void processUsersFile(std::string filePath, std::map<int, User*> &users) {
    std::ifstream usersFile;
    try {
        usersFile.open(filePath);
    }catch (std::ios_base::failure e){
        std::cerr<<"Error opening error file"<<std::endl;
    }
    usersFile.seekg(0);
    while (!usersFile.eof()) {
        std::string userType, name;
        int id;
        usersFile>>userType>>id>>name;
        if (userType == "docente"){
            users.insert(std::make_pair(id, new Teacher(name)));
        }else{
            users.insert(std::make_pair(id, new Student(name)));
        }
    }
    usersFile.close();
}