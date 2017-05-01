#ifndef PROYECTO_THREAD_H
#define PROYECTO_THREAD_H


#include <thread>

class Thread {
private:
    std::thread thread;

public:
    void start();

    void join();

    virtual void run() = 0;

    virtual ~Thread();
};


#endif //PROYECTO_THREAD_H
