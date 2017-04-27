#ifndef SIU_GUARAMINI_TEACHER_H
#define SIU_GUARAMINI_TEACHER_H

#include <string>
#include "serverUser.h"


class Teacher :public User{
private:
    int ID;
    std::string name;


public:
    Teacher(int id, std::string name);

//    virtual void listInscriptions();
};


#endif //SIU_GUARAMINI_TEACHER_H
