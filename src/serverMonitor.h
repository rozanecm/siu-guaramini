#ifndef SIU_GUARAMINI_SERVERMONITOR_H
#define SIU_GUARAMINI_SERVERMONITOR_H


#include <mutex>
#include "server.h"
#include <string>

class serverMonitor {
private:
    server &server1;

    std::mutex m;

public:
    explicit serverMonitor(server &server);

    bool validateClientData(const std::string &userType,
                            const std::string &userIDstring);

    void informDisconnect(const std::string &userType,
                          const std::string &userID);

    void informReceivedCommand(const std::string &userType,
                               const std::string &userID,
                               const char command[3]);

    std::string listSubjects();

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


#endif //SIU_GUARAMINI_SERVERMONITOR_H
