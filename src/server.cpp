#include "serverSubject.h"
#include "serverUser.h"
#include <fstream>
#include <map>
#include <iostream>
#include "server.h"
#include "serverTeacher.h"
#include "serverStudent.h"





void server::processSubjectsFile(std::string filepath) {
    std::ifstream subjectsFile;
    subjectsFile.open(filepath);
    subjectsFile.seekg(0);

    std::string description, subjectID, courseID, teacherID, vacantes;
    while (getline(subjectsFile, subjectID, '\t')) {

        getline(subjectsFile, courseID, '\t');
        getline(subjectsFile, description, '\t');

        getline(subjectsFile, teacherID, '\t');
        getline(subjectsFile, vacantes);

        subjects.emplace(std::make_pair(stoi(subjectID), stoi(courseID)),
                         Subject(stoi(subjectID), stoi(courseID),
                                 stoi(teacherID), stoi(vacantes), description));

        teachers.at(std::stoi(teacherID)).
                setSubjectAndCourseID(std::stoi(subjectID),
                                      std::stoi(courseID));
    }
    subjectsFile.close();
}

void server::processUsersFile(std::string filePath) {
    std::ifstream usersFile;
    usersFile.open(filePath);
    usersFile.seekg(0);

    std::string userType, name, id;
    while (getline(usersFile, userType, '\t')) {
        getline(usersFile, id, '\t');
        getline(usersFile, name, '\n');
        if (userType == "docente"){
            teachers.emplace(std::piecewise_construct,
                             std::make_tuple(stoi(id)),
                             std::make_tuple(stoi(id), name));
        }else{
            students.emplace(std::piecewise_construct,
                             std::make_tuple(stoi(id)),
                             std::make_tuple(stoi(id), name));
        }
    }

    usersFile.close();
}

bool server::isValidID(const int &id, const std::string &userType) {
    if (userType == "alumno"){
        return students.find(id) != students.end();
    }else{
        /* if userType is docente */
        return teachers.find(id) != teachers.end();
    }
}

bool
server::validateClientData(const std::string &userType,
                           const std::string &userIDstring) {
    if (userType == "alumno" || userType == "docente"){
        int userID = std::stoi(userIDstring);
        if (!isValidID(userID, userType)){
            std::cerr<<userIDstring<<" es un "<<userType<<" inválido.\n";
            return false;
        }
        /* output message of new connection */
        std::cerr<<userType<<" "<<userIDstring<<" conectado."<<'\n';
    }else if (userType == "admin"){
        /* output message of new connection */
        std::cerr<<userType<<" conectado."<<'\n';
    }else{
        /* invalid user */
        std::cerr<<userType<<" es un tipo de usuario inválido.\n";
        return false;
    }
    return true;
}

void server::informReceivedCommand(const std::string &userType,
                                   const std::string &userID,
                                   const char *command) {
    if (userType != "admin"){
        std::cerr<<userType<<" "<<userID<<" ejecuta "<<command<<"\n";
    }else{
        std::cerr<<userType<<" ejecuta "<<command<<"\n";
    }
}

void server::informDisconnect(const std::string &userType,
                              const std::string &userID) {
    if (userType != "admin"){
        std::cerr<<userType<<" "<<userID<<" desconectado.\n";
    }else{
        std::cerr<<userType<<" desconectado.\n";
    }
}

std::string server::listSubjects() const{
    std::string returnString;
    for (auto it = subjects.cbegin(); it != subjects.cend(); ++it){
        /* names here are in spanish so it is easier to follow instructions */
        std::string codigoMateria = std::to_string((*it).first.first);
        std::string descripcion = subjects.at((*it).first).getDescription();
        std::string codigoCurso = std::to_string((*it).first.second);
        int teachersID = (*it).second.getTeacherID();
        std::string nombreDocente = teachers.at(teachersID).getName();
        std::string vacantes = std::to_string((*it).second.getVacantes());
        returnString.append(codigoMateria + " - " + descripcion +
                                    ", Curso " + codigoCurso + ", " +
                                    nombreDocente + ", " +
                                    vacantes + " vacantes.\n");
    }
    return returnString;
}

std::string server::listEnrollments(const std::string &userType,
                                    const int &id) {
    if (userType=="alumno"){
        return students.at(id).listEnrollments(subjects,
                                               teachers);
    }else if (userType == "docente"){
        return teachers.at(id).listEnrollments(subjects,
                                               students);
    }
    return std::__cxx11::string();
}

std::string server::enroll(const int &studentID, const int &codigoMateria,
                           const int &codigoCurso) {
    if (!dataForEnrollmentIsValid(studentID, codigoMateria, codigoCurso)){
        return getReasonWhyDataIsNotValid(studentID,
                                          codigoMateria,
                                          codigoCurso);
    }

    students.at(studentID).enroll(codigoMateria, codigoCurso);
    int teacherID = subjects.
            at(std::pair<int, int>(codigoMateria, codigoCurso)).getTeacherID();

    teachers.at(teacherID).enroll(studentID, codigoMateria, codigoCurso);
    subjects.at
            (std::pair<int, int>(codigoMateria, codigoCurso)).enroll(studentID);

    return "Inscripción exitosa.\n";
}

std::string
server::enroll(const int &studentID, const int &subjectID, const int &courseID,
               const int &teacherID) {
    if (teachers.count(teacherID) == 0 ){
        std::string retStrg = "No tiene permisos para operar sobre " +
                              std::to_string(subjectID) +
                              ", curso " + std::to_string(courseID) + ".\n";
        return retStrg;
    }
    return enroll(studentID, subjectID, courseID);
}

std::string server::unEnroll(const int &studentID, const int &codigoMateria,
                           const int &codigoCurso) {
    if (!dataForUnenrollmentIsValid(studentID, codigoMateria, codigoCurso)){
        return "Desinscripción inválida.\n";
    }

    students.at(studentID).unEnroll(codigoMateria, codigoCurso);
    int teacherID = subjects.
            at(std::pair<int, int>(codigoMateria, codigoCurso)).getTeacherID();

    teachers.at(teacherID).unEnroll(studentID);
    subjects.at
            (std::pair<int, int>(codigoMateria, codigoCurso)).
            unEnroll(studentID);

    return "Desinscripción exitosa.\n";
}

std::string
server::unEnroll(const int &studentID, const int &subjectID,
                 const int &courseID,
               const int &teacherID) {
    if (teachers.count(teacherID) == 0 ){
        std::string retStrg = "No tiene permisos para operar sobre " +
                              std::to_string(subjectID) +
                              ", curso " + std::to_string(courseID) + ".\n";
        return retStrg;
    }
    return unEnroll(studentID, subjectID, courseID);
}

bool server::dataForEnrollmentIsValid(const int &id, const int &materia,
                                      const int &curso) {
    return !isStudentAlreadyEnrolled(id, materia, curso) &&
            isValidSubject(materia) &&
            courseExists(curso) &&
            courseHasVacancies(materia, curso);
}

bool server::dataForUnenrollmentIsValid(const int &id, const int &materia,
                                      const int &curso) {
    return isStudentAlreadyEnrolled(id, materia, curso) &&
            isValidSubject(materia) &&
            courseExists(curso);
}

bool
server::isStudentAlreadyEnrolled(const int &studentID, const int &subjectID,
                                 const int &courseID) {
    return students.at(studentID).isEnrolledIn(subjectID, courseID);
}

bool server::isValidSubject(const int &codigoMateria) {
    for (auto it = subjects.cbegin(); it != subjects.cend(); ++it){
        std::string codigoMateriaAlmacenado = std::to_string((*it).first.first);
        if (std::stoi(codigoMateriaAlmacenado) == codigoMateria){
            return true;
        }
    }
    return false;
}

bool server::courseExists(const int &codigoCurso) {
    for (auto it = subjects.cbegin(); it != subjects.cend(); ++it){
        std::string codigoCursoAlmacenado = std::to_string((*it).first.second);
        if (std::stoi(codigoCursoAlmacenado) == codigoCurso){
            return true;
        }
    }
    return false;
}

bool server::courseHasVacancies(const int &materia, const int &curso) {
    return subjects.at(std::pair<int, int>(materia, curso)).hasVacancies();
}

std::string
server::getReasonWhyDataIsNotValid(const int &id, const int &materia,
                                   const int &curso) {
    if (isStudentAlreadyEnrolled(id, materia, curso)){
        return "Inscripción ya realizada.\n";
    }else if (!isValidSubject(materia)){
        std::string retStrg = "La materia " + std::to_string(materia) +
                " no es válida.\n";
        return retStrg;
    }else if (!courseExists(curso)){
        std::string retStrg = "El curso " + std::to_string(curso) +
                " en la materia " + std::to_string(materia) +
                " no es válido.\n";
        return retStrg;
    }else{
        /* course has no vacancies */
        std::string retStrg = "El curso " + std::to_string(curso) +
                              " de la materia " + std::to_string(materia) +
                              " no posee más vacantes.\n";
        return retStrg;
    }
}
