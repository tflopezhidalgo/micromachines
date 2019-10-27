#ifndef MICROMACHINES_DISPATCHER_H
#define MICROMACHINES_DISPATCHER_H

#include "Action.h"
#include "../common/Thread.h"
#include "ProtectedQueue.h"
#include "../common/Proxy.h"

class Dispatcher: public Thread {
    private:
        ProtectedQueue<Action>& q;
        Proxy& proxy;
        bool alive;

    public:
        Dispatcher(ProtectedQueue<Action>& q, Proxy& proxy);
        void run();
        void stop();

};
#endif
