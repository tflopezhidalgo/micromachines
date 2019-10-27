#ifndef MICROMACHINES_EVENTLISTENER_H
#define MICROMACHINES_EVENTLISTENER_H

#include <SDL2/SDL_events.h>
#include "../common/Thread.h"
#include "Action.h"
#include "ProtectedQueue.h"

class EventListener: public Thread{
private:
    ProtectedQueue<Action>& q;

public:
    EventListener(ProtectedQueue<Action>& e);
    void run() override;
    Action handle(SDL_Event e);
    ~EventListener();
};
#endif
