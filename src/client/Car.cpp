#include "Car.h"
#include "BaseSprite.h"
#include "Window.h"

#define CAR_H 50
#define CAR_W 50

// H y W estan deprecados

Car::Car(const std::string &file, int h, int w, Window& win) :
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
    return x + CAR_W / 2;
}

int Car::getYPos() {
    return y + CAR_W / 2;
}

void Car::render(Camera& cam) {
    this->sprite.render( x , y , this->angle,  cam);
}

Car::~Car() { }