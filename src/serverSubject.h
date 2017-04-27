#ifndef SIU_GUARAMINI_SUBJECT_H
#define SIU_GUARAMINI_SUBJECT_H

#include <string>

class Subject {
private:
    int subjectID;
    int courseID;
    int teacherID;
    int vacantes;   //todo translate name
    std::string description;

public:
    Subject(int subjectID, int courseID, int teacherID, int vacantes, std::string description);
};


#endif //SIU_GUARAMINI_SUBJECT_H
