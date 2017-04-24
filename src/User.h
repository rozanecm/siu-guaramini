#ifndef SIU_GUARAMINI_USER_H
#define SIU_GUARAMINI_USER_H


class User {
private:
    int ID;
    std::string name;

public:
    void listSubjects();
    virtual void listInscriptions();
    virtual void enroll();
    virtual void unEnroll();
};


#endif //SIU_GUARAMINI_USER_H
