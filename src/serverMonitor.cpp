#include "serverMonitor.h"
#include <string>
#include "serverLock.h"


serverMonitor::serverMonitor(server &server) : server1(server){ }

bool serverMonitor::validateClientData(const std::string &userType,
                                       const std::string &userIDstring) {
    return server1.validateClientData(userType, userIDstring);
}

void serverMonitor::informDisconnect(const std::string &userType,
                                     const std::string &userID) {
    Lock l(m);
    server1.informDisconnect(userType, userID);
}

void serverMonitor::informReceivedCommand(const std::string &userType,
                                          const std::string &userID,
                                          const char *command) {
    Lock l(m);
    server1.informReceivedCommand(userType, userID, command);
}

std::string serverMonitor::listSubjects() {
    return server1.listSubjects();
}

std::string
serverMonitor::listEnrollments(const std::string &userType, const int &id) {
    return server1.listEnrollments(userType, id);
}

std::string
serverMonitor::enroll(const int &studentID, const int &codigoMateria,
                      const int &codigoCurso) {
    Lock l(m);
    return server1.enroll(studentID, codigoMateria, codigoCurso);
}

std::string serverMonitor::enroll(const int &studentID, const int &subjectID,
                                  const int &courseID, const int &teacherID) {
    Lock l(m);
    return server1.enroll(studentID, subjectID, courseID, teacherID);
}

std::string
serverMonitor::unEnroll(const int &studentID, const int &codigoMateria,
                        const int &codigoCurso) {
    Lock l(m);
    return server1.unEnroll(studentID, codigoMateria, codigoCurso);
}

std::string serverMonitor::unEnroll(const int &studentID, const int &subjectID,
                                    const int &courseID, const int &teacherID) {
    Lock l(m);
    return server1.unEnroll(studentID, subjectID, courseID, teacherID);
}
