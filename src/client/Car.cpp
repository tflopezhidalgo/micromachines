#include "Car.h"
#include "BaseSprite.h"
#include "Window.h"

Car::Car(const std::string &file, int h, int w, Window& win) :
    sprite(win, file, 100, 100) {
        this->x = 0;
        this->y = 0;
        this->health = 0;
}

void Car::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

void Car::render() {
    this->sprite.render();
}
