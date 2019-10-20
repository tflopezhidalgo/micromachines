#ifndef MICROMACHINES_PROTECTEDQUEUE_H
#define MICROMACHINES_PROTECTEDQUEUE_H

#include <queue>
#include <mutex>
#include <stdexcept>

template <class T>
class ProtectedQueue {
    private:
        std::queue<T> q;
        std::mutex m;
        int maxSize;
        int actualSize;

    public:
        ProtectedQueue(int maxSize) {
            this->maxSize = maxSize;
            this->actualSize = 0;
        }

        void push(T object){
            std::unique_lock<std::mutex> lck(m);
            if (actualSize >= maxSize)
                throw std::runtime_error("Limite de cola excedida");

            actualSize += 1;
            q.push(std::move(object));
        }

        T pop() {
            std::unique_lock<std::mutex> lck(m);
            if (actualSize == 0)
                throw std::runtime_error("Cola vacia");

            actualSize -= 1;
            T returnValue(std::move(q.front()));
            q.pop();
            return returnValue;
        }

        ~ProtectedQueue() {

        }
};
#endif
