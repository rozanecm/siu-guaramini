#ifndef SIU_GUARAMINI_STUDENT_H
#define SIU_GUARAMINI_STUDENT_H

#include <string>
#include "serverUser.h"

class Student : public User{
private:
    int ID;
    std::string name;

public:
//    virtual void listInscriptions();
//    virtual void enroll();
//    virtual void unEnroll();

    Student(int id, std::string name);
};


#endif //SIU_GUARAMINI_STUDENT_H
