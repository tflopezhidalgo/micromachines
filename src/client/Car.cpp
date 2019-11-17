#include "Car.h"
#include "Sprite.h"
#include "Window.h"
#include "Constants.h"
#include "AnimatedSprite.h"
#include "Identifiers.h"

Car::Car(const std::string &file, Window& win) :
    sprite(win, file, CAR_H, CAR_W),
    animation(win, "../media/animations/fire.png", 7, 185, 191, 15, 15),
    health(win){
        this->x = 0;
        this->y = 0;
        this->angle = 0;
        this->exploding = false;
}

void Car::setState(int x, int y, int angle, int health, bool exploding) {
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->health.setActualHealth(health);
    this->exploding = exploding;
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

void Car::render(Camera& cam) {
    if (!exploding && health.getHealth() != 0) {
        this->health.renderAt(x, y, cam);
        this->sprite.render(x, y, this->angle, cam);
    } else {
        this->animation.render(x, y, 0, cam);
    }
}

Car::~Car() { }