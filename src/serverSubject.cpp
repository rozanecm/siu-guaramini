#include "serverSubject.h"

Subject::Subject(int teacherID, int vacantes, std::string description) {
    this->teacherID = teacherID;
    this->vacantes = vacantes;
    this->description = description;
}
