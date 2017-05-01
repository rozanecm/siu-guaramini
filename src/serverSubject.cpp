#include "serverSubject.h"

Subject::Subject(int subjectID, int courseID, int teacherID, int vacantes,
                 std::string description) : subjectID(subjectID),
                                            courseID(courseID),
                                            teacherID(teacherID),
                                            vacantes(vacantes),
                                            description(description){}

std::string Subject::getDescription() const {
    return description;
}

int Subject::getVacantes() const {
    return vacantes;
}

int Subject::getTeacherID() const {
    return teacherID;
}

void Subject::enroll(int studentID) {
    enrolledStudents.push_front(studentID);
    vacantes--;
}

void Subject::unEnroll(int studentID) {
    enrolledStudents.remove(studentID);
    vacantes++;
}

bool Subject::hasVacancies() {
    return vacantes > 0;
}
