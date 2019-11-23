#ifndef MICROMACHINES_DISPATCHER_H
#define MICROMACHINES_DISPATCHER_H

#include "../common/Thread.h"
#include "ProtectedQueue.h"
#include "../common/Proxy.h"
#include "../common/Event.h"

class Dispatcher: public Thread {
    private:
        ProtectedQueue<Event>& q;
        Proxy& proxy;
        bool alive;

    public:
        Dispatcher(ProtectedQueue<Event>& q, Proxy& proxy);
        void run();
        void stop();
        ~Dispatcher();
};
#endif
