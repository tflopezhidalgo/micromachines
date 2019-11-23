#ifndef MICROMACHINES_EVENTLISTENER_H
#define MICROMACHINES_EVENTLISTENER_H

#include <SDL2/SDL_events.h>
#include "../common/Thread.h"
#include "ProtectedQueue.h"
#include "../common/Event.h"
#include "ffmpeg/RecorderHandle.h"

class EventListener: public Thread{
private:
    bool alive;
    std::map<int, bool> keysHeld;
    ProtectedQueue<Event>& q;
	std::string playerID;
	RecorderHandle& recorderHandle;

public:
    EventListener(std::string playerID, 
				  ProtectedQueue<Event>& e,
				  RecorderHandle& recorderHandle);
    void run() override;
    void detectEvent(SDL_Event& e);
    std::vector<char> createActionList();
    ~EventListener();
};
#endif
