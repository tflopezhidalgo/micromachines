#include "EventListener.h"
#include "Sound.h"

EventListener::EventListener(std::string& playerID,
							 ProtectedQueue<Event>& q,
							 RecorderHandle& recorderHandle):
							 alive(true),
                             q(q),
                             playerID(playerID),
                             recorderHandle(recorderHandle),
                             accelerating("../media/sounds/accelerating_sound.wav"),
                             brake("../media/sounds/brake_sound.wav") {}

void EventListener::run() {
    SDL_Event e;

    std::vector<char> lastActions;

    while (alive) {
        // Mejor : 15000
        usleep(15000);

        if (SDL_PollEvent(&e))
            detectEvent(e);

        std::vector<char> actions = std::move(createActionList());

        if (actions == lastActions)
            continue;

        if (actions.empty() && lastActions.size()){
            Event event(this->playerID, {'E'});
            q.push(std::move(event));
            lastActions = std::move(actions);
        }

        if (!actions.empty()) {
            Event event(this->playerID, actions);
            q.push(std::move(event));
            lastActions = std::move(actions);
        }
    }
}

void EventListener::detectEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        keysHeld[e.key.keysym.sym] = true;
        if (e.key.keysym.sym == SDLK_w)
            accelerating.play();
        if (e.key.keysym.sym == SDLK_s)
            brake.play();
    }

    if (e.type == SDL_KEYUP) {
        keysHeld[e.key.keysym.sym] = false;
        if (e.key.keysym.sym == SDLK_w)
            accelerating.stop();
        if (e.key.keysym.sym == SDLK_s)
            brake.stop();
    }
}

std::vector<char> EventListener::createActionList() {
    std::vector<char> actions;

    if (this->keysHeld[SDLK_w]) {
        actions.push_back(FORWARD);
    }

    if (this->keysHeld[SDLK_s]) {
        actions.push_back(BACKWARD);
    }

    if (this->keysHeld[SDLK_d]) {
        actions.push_back(RIGHT);
    }

    if (this->keysHeld[SDLK_a]) {
        actions.push_back(LEFT);
    }

    if (this->keysHeld[SDLK_f]) {
        recorderHandle.stopRecorder();
    }

    if (this->keysHeld[SDLK_g]) {
        recorderHandle.startRecorder();
    }

    if (this->keysHeld[SDLK_q]) {
        actions.clear();
        actions.push_back('Q');
        alive = false;
    }

    return actions;
}

void EventListener::stop() {
    alive = false;
}

EventListener::~EventListener() {

}
