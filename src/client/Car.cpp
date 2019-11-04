#include "Car.h"
#include "BaseSprite.h"
#include "Window.h"
#include "Macros.h"

Car::Car(const std::string &file, Window& win) :
    sprite(win, file, CAR_H, CAR_W) {
        this->x = 0;
        this->y = 0;
        this->health = 0;
        this->angle = 0;
}

void Car::setPos(int x, int y, int angle) {
    this->x = x;
    this->y = y;
    this->angle = angle;
}

int Car::getXPos() {
    return x;
}

int Car::getYPos() {
    return y;
}

void Car::render(Camera& cam) {
    this->sprite.render(x, y, this->angle, cam);
}

Car::~Car() { }