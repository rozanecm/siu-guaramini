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

    while (subjectsFile.peek() != EOF) {
        std::string description, subjectID, courseID, teacherID, vacantes;

        getline(subjectsFile, subjectID, '\t');
        getline(subjectsFile, courseID, '\t');
        getline(subjectsFile, description, '\t');

        getline(subjectsFile, teacherID, '\t');
        getline(subjectsFile, vacantes);

        subjects.emplace(std::make_pair(stoi(subjectID), stoi(courseID)),
                         Subject(stoi(subjectID), stoi(courseID),
                                 stoi(teacherID), stoi(vacantes), description));
    }
    subjectsFile.close();
}

void server::processUsersFile(std::string filePath) {
    std::ifstream usersFile;
    usersFile.open(filePath);
    usersFile.seekg(0);

    while (!usersFile.eof()) {
        std::string userType, name;
        int id;
        usersFile>>userType>>id>>name;
        if (userType == "docente"){
            teachers.emplace(std::piecewise_construct, std::make_tuple(id),
                             std::make_tuple(id, name));
//            teachers.emplace(id, id, name);
//            teachers.emplace(id, Teacher(id, name));
//            teachers.insert(std::make_pair(id, new Teacher(name)));
        }else{
//            students[id] = Student(id, name);
            students.emplace(std::piecewise_construct, std::make_tuple(id),
                             std::make_tuple(id, name));
//            students.emplace(id, id, name);
//            students.emplace(id, Student(id, name));
//            students.insert(std::make_pair(id, new Student(name)));
        }
    }

    usersFile.close();
}