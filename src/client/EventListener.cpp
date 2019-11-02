#include "EventListener.h"
#include <string>
#include <SDL2/SDL.h>
#include <zconf.h>
#include <Macros.h>
#include "../common/Event.h"

EventListener::EventListener(std::string playerID, 
							 ProtectedQueue<Event>& q):
    q(q), playerID(playerID) {}

void EventListener::run() {
    SDL_Event e;
    while (alive) {

        /* Si se pone muy rápido el server tiene más para
         * desencolar (ya que desencola hasta que se vacia)
         * y aplicar sobre el modelo, esto provoca que todo
         * se mueva más rápido
         */
        usleep(15000);

        if (SDL_PollEvent(&e))
            detectEvent(e);

        std::vector<char> actions = std::move(createActionList());
        //if (!actions.empty()) {
            Event event(this->playerID, std::move(actions));
            q.push(std::move(event));
        //}
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

    if (this->keysHeld[SDLK_q])
        this->alive = false;

    return actions;
}

EventListener::~EventListener() {}
