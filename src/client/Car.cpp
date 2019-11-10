#include "Car.h"
#include "BaseSprite.h"
#include "Window.h"
#include "Constants.h"

Car::Car(const std::string &file, Window& win) :
    sprite(win, file, CAR_H, CAR_W),
    health(win){
        this->x = 0;
        this->y = 0;
        this->angle = 0;
}

void Car::setState(int x, int y, int angle, int health) {
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->health.setActualHealth(health);
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
    this->sprite.render(x, y, this->angle, cam);
    this->health.renderAt(x, y, cam);
}

Car::~Car() { }