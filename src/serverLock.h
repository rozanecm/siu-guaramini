#ifndef PROYECTO_LOCK_H
#define PROYECTO_LOCK_H


#include <mutex>

class Lock {
private:
    std::mutex &m;

public:
    explicit Lock(std::mutex  &m);

    ~Lock();
};


#endif //PROYECTO_LOCK_H
