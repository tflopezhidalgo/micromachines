#ifndef MICROMACHINES_RECEIVER_H
#define MICROMACHINES_RECEIVER_H

#include "../common/Thread.h"
#include "../common/Socket.h"

class Receiver: public Thread {
    private:

    public:
        Receiver();
        void start();

};

#endif
