#ifndef MICROMACHINES_PROTECTEDQUEUE_H
#define MICROMACHINES_PROTECTEDQUEUE_H

#include <queue>
#include <mutex>

template <class T>
class ProtectedQueue {
private:
    std::queue<T> q;
    std::mutex m;
public:
    ProtectedQueue() {}

    void push(T object) {
        std::unique_lock<std::mutex> lck(m);
        q.push(std::move(object));
    }

    T pop() {
        T returnValue(std::move(q.front()));
        q.pop();
        return std::move(returnValue);
    }

    std::vector<T> emptyQueue() {
        std::unique_lock<std::mutex> lck(m);
        std::vector<T> values;
        while (!q.empty()) {
            T poppedValue = this->pop();
            values.push_back(std::move(poppedValue));
        }
        return std::move(values);
    }

    ~ProtectedQueue() {}
};

#endif //MICROMACHINES_PROTECTEDQUEUE_H
