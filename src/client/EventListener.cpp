#include "EventListener.h"
#include "Window.h"
#include <string>
#include "BaseSprite.h"
#include "Camera.h"
#include "TileMap.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <zconf.h>
#include "../common/Event.h"

EventListener::EventListener(std::string playerID, 
							 ProtectedQueue<Event>& q):
    q(q), playerID(playerID) {}

void EventListener::run() {
    bool alive = true;
    SDL_Event e;
    while (alive) {
        usleep(2);
        while (SDL_PollEvent(&e)) {

            // Ojo que si catchea cosas inválidas no tiene que encolar nada
            Event action(std::move(this->handle(e)));
            q.push(std::move(action));
        }
    }
}

Event EventListener::handle(SDL_Event e){
        switch (e.key.keysym.sym) {
            case SDLK_w:
                return Event(this->playerID, FORWARD);
            case SDLK_s:
                return Event(this->playerID, BACKWARD);
            case SDLK_a:
                return Event(this->playerID, LEFT);
            case SDLK_d:
                return Event(this->playerID, RIGHT);
            default:
                return Event(this->playerID, QUIT);
        }
    /*} else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
                return Event(str, FORWARD);
            case SDLK_s:
                return Event(str, BACKWARD);
            case SDLK_a:
                return Event(str, LEFT);
            case SDLK_d:
                return Event(str, RIGHT);
            default:
                return Event(str, QUIT);
        }
    }*/
}

EventListener::~EventListener() {
}
