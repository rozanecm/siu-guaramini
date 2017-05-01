#include "commonTPException.h"

TPException::TPException(std::string msg) : msg(msg){}

const char *TPException::what() const noexcept {
    return msg.c_str();
}
