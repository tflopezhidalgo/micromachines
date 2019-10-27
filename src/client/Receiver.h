#ifndef MICROMACHINES_RECEIVER_H
#define MICROMACHINES_RECEIVER_H

#include "../common/Thread.h"
#include "../common/Socket.h"
#include "ProtectedModel.h"
#include "Proxy.h"

class Receiver: public Thread {
    private:
        ProtectedModel& model;
        bool alive;
        Proxy& proxy;

    public:
        explicit Receiver(ProtectedModel& model,
                          Proxy& proxy);
        explicit Receiver(ProtectedModel& model);
        void run();
        void stop();

};

#endif
