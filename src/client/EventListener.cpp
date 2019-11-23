#include "EventListener.h"
#include <string>
#include <SDL2/SDL.h>
#include <zconf.h>
#include <Constants.h>
#include "../common/Event.h"

EventListener::EventListener(std::string playerID, 
							 ProtectedQueue<Event>& q,
							 RecorderHandle& recorderHandle):
							 alive(true),
                             q(q),
                             playerID(playerID),
                             recorderHandle(recorderHandle) {}

void EventListener::run() {
    SDL_Event e;
    while (alive) {
        // Mejor : 15000
        usleep(15000);

        if (SDL_PollEvent(&e))
            detectEvent(e);

        std::vector<char> actions = std::move(createActionList());
        if (!actions.empty()) {
            Event event(this->playerID, std::move(actions));
            q.push(std::move(event));
        }
    }
}

void EventListener::detectEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN)
        keysHeld[e.key.keysym.sym] = true;

    if (e.type == SDL_KEYUP)
        keysHeld[e.key.keysym.sym] = false;
}

std::vector<char> EventListener::createActionList() {
    std::vector<char> actions;

    if (this->keysHeld[SDLK_w])
        actions.push_back(FORWARD);

    if (this->keysHeld[SDLK_s])
        actions.push_back(BACKWARD);

    if (this->keysHeld[SDLK_d])
        actions.push_back(RIGHT);

    if (this->keysHeld[SDLK_a])
        actions.push_back(LEFT);

    if (this->keysHeld[SDLK_f])
        recorderHandle.stopRecorder();

    if (this->keysHeld[SDLK_g])
        recorderHandle.startRecorder();

    if (this->keysHeld[SDLK_q]) {
        actions.clear();
        actions.push_back('Q');
        alive = false;
    }

    return actions;
}

EventListener::~EventListener() {}
