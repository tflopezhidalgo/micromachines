#ifndef MICROMACHINES_EVENTLISTENER_H
#define MICROMACHINES_EVENTLISTENER_H

#include <SDL2/SDL_events.h>
#include "../common/Thread.h"
#include "Action.h"
#include "ProtectedQueue.h"
#include "../common/Event.h"

class EventListener: public Thread{
private:
    ProtectedQueue<Event>& q;
	std::string playerID;

public:
    EventListener(std::string playerID, 
				  ProtectedQueue<Event>& e);
    void run() override;
    Event handle(SDL_Event e);
    ~EventListener();
};
#endif
