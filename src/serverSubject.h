#ifndef SIU_GUARAMINI_SUBJECT_H
#define SIU_GUARAMINI_SUBJECT_H

#include <string>
#include "server.h"

class Subject {
private:
    int subjectID;
    int courseID;
    int teacherID;
    int vacantes;   //todo translate name
    std::string description;
    std::forward_list<int> enrolledStudents;

public:
    Subject(int subjectID, int courseID, int teacherID, int vacantes,
            std::string description);

    int getTeacherID() const;

    int getVacantes() const;

    std::string getDescription() const;

    void enroll(int studentID);

    void unEnroll(int studentID);

    bool hasVacancies();
};


#endif //SIU_GUARAMINI_SUBJECT_H
