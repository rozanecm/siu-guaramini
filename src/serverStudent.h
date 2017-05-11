#ifndef SIU_GUARAMINI_STUDENT_H
#define SIU_GUARAMINI_STUDENT_H

#include <string>
#include <utility>
#include <forward_list>
#include <map>
#include "serverSubject.h"
#include "serverTeacher.h"

class Student {
private:
    int ID;

    std::string name;

    std::forward_list<std::pair<int, int>> enrolledSubjects;
    /* enrolledSubjects pair: <codigoMateria, codigoCurso> */

public:
    std::string
    listEnrollments(const std::map<std::pair<int, int>, Subject> &subjects,
                    const std::map<int, Teacher> &teachers);

    void enroll(int codigoMateria, int codigoCurso);

    void unEnroll(int codigoMateria, int codigoCurso);

    bool isEnrolledIn(const int &subjectID, const int &courseID);

    std::string getName() const;

    Student(int id, std::string name);
};


#endif //SIU_GUARAMINI_STUDENT_H
