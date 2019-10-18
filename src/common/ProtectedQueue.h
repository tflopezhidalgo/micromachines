#ifndef MICROMACHINES_PROTECTEDQUEUE_H
#define MICROMACHINES_PROTECTEDQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class ProtectedQueue {
    private:
        std::queue<T> q;
        std::mutex m;

    public:
        ProtectedQueue() {

        }

        void push(T object){

        }

        T pop() {

        }

        ~ProtectedQueue() {

        }
};
#endif
