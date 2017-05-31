#ifndef SIU_GUARAMINI_SERVER_H
#define SIU_GUARAMINI_SERVER_H


#include <map>
#include "serverStudent.h"
#include "serverTeacher.h"
#include "serverSubject.h"
#include <string>
#include <utility>

class Subject;

class server {
private:
    std::map<int, Student> students;    /* map<id, Student> */
    std::map<int, Teacher> teachers;    /* map<id, Teacher> */
    std::map<std::pair<int, int>, Subject> subjects;
    /* codigo materia - codigo curso - Subject */

    bool isValidID(const int &id, const std::string &userType);

    bool dataForEnrollmentIsValid(const int &id, const int &materia,
                                  const int &curso);

    bool dataForUnenrollmentIsValid(const int &id, const int &materia,
                                  const int &curso);

    bool isStudentAlreadyEnrolled(const int &studentID, const int &subjectID,
                                  const int &courseID);

    bool isValidSubject(const int &codigoMateria);

    bool courseExists(const int &codigoCurso);

    bool courseHasVacancies(const int &materia, const int &curso);

    std::string getReasonWhyDataIsNotValid(const int &id, const int &materia,
                                           const int &curso);

public:
    void processUsersFile(const std::string &filePath);

    void processSubjectsFile(const std::string &filepath);

    bool validateClientData(const std::string &userType,
                            const std::string &userIDstring);

    void informReceivedCommand(const std::string &userType,
                               const std::string &userID,
                               const char command[3]);

    void informDisconnect(const std::string &userType,
                          const std::string &userID);

    std::string listSubjects() const;

    std::string listEnrollments(const std::string &userType, const int &id);

    std::string enroll(const int &studentID, const int &codigoMateria,
                       const int &codigoCurso);

    std::string
    enroll(const int &studentID, const int &subjectID, const int &courseID,
           const int &teacherID);

    std::string unEnroll(const int &studentID, const int &codigoMateria,
                       const int &codigoCurso);

    std::string
    unEnroll(const int &studentID, const int &subjectID, const int &courseID,
           const int &teacherID);
};


#endif //SIU_GUARAMINI_SERVER_H
