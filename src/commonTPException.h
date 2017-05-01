#ifndef SIU_GUARAMINI_COMMONTPEXCEPTION_H
#define SIU_GUARAMINI_COMMONTPEXCEPTION_H


#include <exception>
#include <string>

class TPException : public std::exception{
private:
    std::string msg;
public:
    TPException(std::string msg);

    virtual const char* what() const noexcept ;
};


#endif //SIU_GUARAMINI_COMMONTPEXCEPTION_H
