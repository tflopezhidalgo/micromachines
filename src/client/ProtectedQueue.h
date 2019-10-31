#ifndef MICROMACHINES_PROTECTEDQUEUE_H
#define MICROMACHINES_PROTECTEDQUEUE_H

#include <queue>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <condition_variable>

// Implementa cola bloqueante sólo para el pop

template <class T>
class ProtectedQueue {
    private:
        std::queue<T> q;
        std::mutex m;
        std::condition_variable cv;

    public:
        ProtectedQueue() {}

        void push(T object){
            std::unique_lock<std::mutex> lck(m);
            q.push(std::move(object));
            cv.notify_all();
        }

        T pop() {
            std::unique_lock<std::mutex> lck(this->m);
            std::cout << "Comienza pop " << std::endl;
            while (q.empty())
                cv.wait(lck);

            T returnValue(std::move(q.front()));
            q.pop();
            std::cout << "Termina pop " << std::endl;
            return returnValue;
        }

        ~ProtectedQueue() {

        }
};
#endif
