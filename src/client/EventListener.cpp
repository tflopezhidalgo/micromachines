#include "EventListener.h"
#include <string>
#include <SDL2/SDL.h>
#include <zconf.h>
#include <Constants.h>
#include "../common/Event.h"

EventListener::EventListener(std::string playerID, 
							 ProtectedQueue<Event>& q):
    q(q), playerID(playerID) {}

void EventListener::run() {
    SDL_Event e;
    while (alive) {

        //tunear
        usleep(15000);

        std::vector<char> actions;
        if (SDL_PollEvent(&e)) {
            handle(e);
        }

        if (keysHeld[SDLK_w]) {
            actions.push_back(FORWARD);
        }
        if (keysHeld[SDLK_s]) {
            actions.push_back(BACKWARD);
        }
        if (keysHeld[SDLK_d]) {
            actions.push_back(RIGHT);
        }
        if (keysHeld[SDLK_a]) {
            actions.push_back(LEFT);
        }

        Event event(this->playerID, actions);
        q.push(std::move(event));
    }
}

void EventListener::handle(SDL_Event& e) {
    if (e.type == SDL_QUIT) {
        alive = false;
    }
    if (e.type == SDL_KEYDOWN) {
        keysHeld[e.key.keysym.sym] = true;
    }
    if (e.type == SDL_KEYUP) {
        keysHeld[e.key.keysym.sym] = false;
    }
    if (keysHeld[SDLK_ESCAPE]) {
        alive = false;
    }
}

EventListener::~EventListener() {}
