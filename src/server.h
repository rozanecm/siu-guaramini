#ifndef SIU_GUARAMINI_SERVER_H
#define SIU_GUARAMINI_SERVER_H


#include "serverStudent.h"
#include "serverTeacher.h"

class server {
private:
    std::map<int, Student> students;
    std::map<int, Teacher> teachers;
    std::map<std::pair<int, int>, Subject> subjects;

public:
    void processSubjectsFile(std::string filepath);

    void processUsersFile(std::string filePath);
};


#endif //SIU_GUARAMINI_SERVER_H
