#include "serverSubject.h"

Subject::Subject(int subjectID, int courseID, int teacherID, int vacantes,
                 std::string description) : subjectID(subjectID),
                                            courseID(courseID),
                                            teacherID(teacherID),
                                            vacantes(vacantes),
                                            description(description){
//    this->teacherID = teacherID;
//    this->vacantes = vacantes;
//    this->description = description;
}
