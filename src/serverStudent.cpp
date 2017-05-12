#include <algorithm>
#include <utility>
#include <string>
#include <map>
#include "serverStudent.h"

Student::Student(int id, std::string name) : ID(id), name(name){}

void Student::enroll(int codigoMateria, int codigoCurso) {
    enrolledSubjects.push_front(std::pair<int, int>(codigoMateria,
                                                    codigoCurso));
}

void Student::unEnroll(int codigoMateria, int codigoCurso) {
    enrolledSubjects.remove(std::pair<int, int>(codigoMateria, codigoCurso));
}

bool Student::isEnrolledIn(const int &subjectID, const int &courseID) {
    return enrolledSubjects.end() !=
            std::find(enrolledSubjects.begin(),
                      enrolledSubjects.end(),
                      std::pair<int, int>(subjectID, courseID));
}

std::string
Student::listEnrollments(const std::map<std::pair<int, int>, Subject> &subjects,
                         const std::map<int, Teacher> &teachers) {
    enrolledSubjects.sort();
    std::string retStrng;
    for (auto it = enrolledSubjects.begin(); it != enrolledSubjects.end();
         ++it){
        retStrng.append(std::to_string((*it).first));
        retStrng.append(" - ");
        retStrng.append(subjects.at((*it)).getDescription());
        retStrng.append(", Curso ");
        retStrng.append(std::to_string((*it).second));
        retStrng.append(", ");
        retStrng.append(teachers.at(subjects.at((*it)).getTeacherID()).
                getName());
        retStrng.append(".\n");
    }
    return retStrng;
}

std::string Student::getName() const {
    return name;
}
