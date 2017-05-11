#include "commonTPException.h"
#include <string>

TPException::TPException(std::string msg) : msg(msg){}

const char *TPException::what() const noexcept {
    return msg.c_str();
}
