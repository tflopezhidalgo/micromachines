#include "EventListener.h"
#include "Window.h"
#include "BaseSprite.h"
#include "Camera.h"
#include "TileMap.h"
#include <SDL2/SDL.h>
#include <iostream>

EventListener::EventListener(ProtectedQueue<Action>& q) :
    q(q) {}

void EventListener::run() {
    bool alive = true;
    SDL_Event e;
    while (alive) {
        while (SDL_PollEvent(&e)) {
            Action action(std::move(this->handle(e)));
            q.push(std::move(action));
        }
    }
}

Action EventListener::handle(SDL_Event e){
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
                return Action(FORWARD);
            case SDLK_s:
                return Action(BACKWARD);
            case SDLK_a:
                return Action(LEFT);
            case SDLK_d:
                return Action(RIGHT);
            case SDLK_q:
                return Action(QUIT);
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
                return Action(FORWARD);
            case SDLK_s:
                return Action(BACKWARD);
            case SDLK_a:
                return Action(LEFT);
            case SDLK_d:
                return Action(RIGHT);
            case SDLK_q:
                return Action(QUIT);
        }
    }
}

EventListener::~EventListener() {
}