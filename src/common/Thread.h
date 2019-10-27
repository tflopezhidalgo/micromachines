//
// Created by leobellaera on 19/9/19.
//

#ifndef FRAME_OF_REFERENCE_THREAD_H
#define FRAME_OF_REFERENCE_THREAD_H

#include <thread>

class Thread {
private:
    std::thread thread;
public:
    Thread();
    void start();
    void join();
    virtual void run() = 0;
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread(Thread&& other);
    Thread& operator=(Thread&& other);
    virtual ~Thread();
};

#endif //FRAME_OF_REFERENCE_THREAD_H
