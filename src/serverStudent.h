#ifndef SIU_GUARAMINI_STUDENT_H
#define SIU_GUARAMINI_STUDENT_H

#include <string>
#include "serverUser.h"

class Student : public User{
private:
    std::string name;

public:
//    virtual void listInscriptions();
//    virtual void enroll();
//    virtual void unEnroll();

    Student(std::string name);
};


#endif //SIU_GUARAMINI_STUDENT_H
