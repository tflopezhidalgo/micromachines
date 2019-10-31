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

EventListener::EventListener(ProtectedQueue<Event>& q) :
    q(q) {}

void EventListener::run() {
    bool alive = true;
    SDL_Event e;
    while (alive) {
        while (SDL_PollEvent(&e)) {

            // Ojo que si catchea cosas inválidas no tiene que encolar nada
            usleep(1);
            Event action(std::move(this->handle(e)));
            q.push(std::move(action));
        }
    }
}

Event EventListener::handle(SDL_Event e){
    std::string str("q");
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
                return Event(str, FORWARD);
            case SDLK_s:
                return Event(str, BACKWARD);
            case SDLK_a:
                return Event(str, LEFT);
            case SDLK_d:
                return Event(str, RIGHT);
            case SDLK_q:
                return Event(str, QUIT);
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
                return Event(str, FORWARD);
            case SDLK_s:
                return Event(str, BACKWARD);
            case SDLK_a:
                return Event(str, LEFT);
            case SDLK_d:
                return Event(str, RIGHT);
            case SDLK_q:
                return Event(str, QUIT);
        }
    }

    return Event(str, NO_OP);
}

EventListener::~EventListener() {
}