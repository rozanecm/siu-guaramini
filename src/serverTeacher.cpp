#include "serverTeacher.h"
#include <utility>
#include <string>
#include <map>
#include <sstream>
#include "serverSubject.h"

Teacher::Teacher(int id, std::string name) : ID(id), name(name){}

std::string Teacher::getName() const {
    return name;
}

void Teacher::enroll(int studentID, int codigoMateria, int codigoCurso) {
    enrolledStudents[studentID] =
            std::pair<int, int>(codigoMateria, codigoCurso);
}

void Teacher::unEnroll(int studentID) {
    enrolledStudents.erase(studentID);
}

std::string
Teacher::listEnrollments(const std::map<std::pair<int, int>, Subject> &subjects,
                         const std::map<int, Student> &students) {
    /* construct first line of msg */
    /* insert subject ID */
    std::stringstream retMsg;
    retMsg<<std::to_string(subjectID)<<" - ";
    /* insert description */
    retMsg<<(subjects.at(std::pair<int, int>(subjectID, courseID)).
            getDescription());
    /* insert course ID */
    retMsg<<(", Curso " + std::to_string(courseID) + ", ");
    /* insert prof. name */
    retMsg<<(name + ".\n");
    /* insert students' names */
    for (auto it = enrolledStudents.cbegin(); it != enrolledStudents.cend();
         ++it){
        int studentID = (*it).first;
        /* insert student's id */
        retMsg<<(std::to_string(studentID) + " ");
        /* insert student's id */
        retMsg<<(students.at(studentID).getName() + "\n");
    }
//    /* construct first line of msg */
//    /* insert subject ID */
//    std::string retMsg = std::to_string(subjectID) + " - ";
//    /* insert description */
//    retMsg.append(subjects.at(std::pair<int, int>(subjectID, courseID)).
//            getDescription());
//    /* insert course ID */
//    retMsg.append(", Curso " + std::to_string(courseID) + ", ");
//    /* insert prof. name */
//    retMsg.append(name + ".\n");
//    /* insert students' names */
//    for (auto it = enrolledStudents.cbegin(); it != enrolledStudents.cend();
//         ++it){
//        int studentID = (*it).first;
//        /* insert student's id */
//        retMsg.append(std::to_string(studentID) + " ");
//        /* insert student's id */
//        retMsg.append(students.at(studentID).getName() + "\n");
//    }
//    return retMsg;
    return retMsg.str();
}

void Teacher::setSubjectAndCourseID(const int &subjectID, const int &courseID) {
    this->subjectID = subjectID;
    this->courseID = courseID;
}
