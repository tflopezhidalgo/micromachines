#include "Car.h"
#include "Sprite.h"
#include "Window.h"
#include "Constants.h"
#include "AnimatedSprite.h"
#include "Identifiers.h"
#include "Sound.h"
#include <SDL2/SDL_mixer.h>

Car::Car(const std::string &file, Window& win) :
    sprite(win, file, CAR_H, CAR_W),
    animation(win, "../media/animations/fire.png", 7, 185, 191, 25, 25),
    health(win),
    crashSound("../media/sounds/exploding.wav") {
        this->x = 0;
        this->y = 0;
        this->angle = 0;
        this->lapsDone = 0;
        this->blinded = false;
    }

void Car::setState(int x, int y, int angle, int health, int lapsDone, bool blinded) {
    this->x = x;
    this->y = y;
    this->angle = angle;
    if (health == 0 && this->health.getHealth() != 0) {
        this->crashSound.play();
    }
    this->health.setActualHealth(health);
    this->lapsDone = lapsDone;
    this->blinded = blinded;
}

int Car::getAngle(){
    return this->angle;
}

int Car::getXPos() {
    return x;
}

int Car::getYPos() {
    return y;
}

bool Car::isBlinded() {
    return blinded;
}

int Car::getLapsDone() {
    return lapsDone;
}

void Car::render(Camera& cam) {
    if (health.getHealth() > 0) {
        this->health.renderAt(x, y, cam);
        this->sprite.render(x, y, this->angle, cam);
    } else {
        this->animation.render(x, y, 0, cam);
    }
}

Car::~Car() { }
