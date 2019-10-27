//
// Created by leobellaera on 26/10/19.
//

#ifndef MICROMACHINES_PROTECTEDQUEUE_H
#define MICROMACHINES_PROTECTEDQUEUE_H

#include <queue>
#include <mutex>

template <class T>
class ProtectedQueue {
private:
    std::queue<T> q;
    std::mutex m;

    T pop() {
        T returnValue(std::move(q.front()));
        q.pop();
        return std::move(returnValue);
    }

public:
    ProtectedQueue() {}

    void push(T object){
        std::unique_lock<std::mutex> lck(m);
        q.push(std::move(object));
    }

    std::vector<T> emptyQueue() {
        std::unique_lock<std::mutex> lck(m);
        std::vector<T> values;
        while (!q.empty()) {
            T poppedValue = this->pop();
            values.push_back(poppedValue);
        }
        return values;
    }

    ~ProtectedQueue() {}
};

#endif //MICROMACHINES_PROTECTEDQUEUE_H
