#ifndef SIU_GUARAMINI_TEACHER_H
#define SIU_GUARAMINI_TEACHER_H

#include <string>
#include <map>
#include "serverUser.h"

class Subject;
class Student;

class Teacher :public User{
private:
    int ID;

    std::string name;

    int subjectID;

    int courseID;

    std::map<int, std::pair<int, int>> enrolledStudents;
    /* key: student ID value: codMateria codCurso */

public:
    Teacher(int id, std::string name);

    std::string getName() const;

    virtual std::string listEnrollments
            (const std::map<std::pair<int, int>, Subject> &subjects,
             const std::map<int, Student> &students);

    virtual void enroll(int studentID, int codigoMateria, int codigoCurso);

    virtual void unEnroll(int studentID);

    void setSubjectAndCourseID(const int &subjectID, const int &courseID);
};


#endif //SIU_GUARAMINI_TEACHER_H
