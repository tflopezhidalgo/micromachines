#include "Throwable.h"

Throwable::Throwable(Throwable&& other) :
sprite(std::move(other.sprite)){
    this->alive = other.alive;
    this->x = other.x;
    this->y = other.y;
}

Throwable::Throwable(BaseSprite sprite, bool alive, int x, int y) :
sprite(sprite){
    this->alive = alive;
    this->x = x;
    this->y = y;
}

void Throwable::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

void Throwable::setState(bool state) {
    this->alive = state;
}

void Throwable::render(Camera &cam) {
    if (alive)
        this->sprite.render(x, y, 0, cam);
}

int Throwable::getXPos() {
    return x;
}

int Throwable::getYPos() {
    return y;
}
