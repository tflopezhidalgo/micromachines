#include "Throwable.h"

Throwable::Throwable(Throwable&& other) :
sprite(std::move(other.sprite)){
    this->state = other.state;
    this->x = other.x;
    this->y = other.y;
}

Throwable::Throwable(BaseSprite sprite, EntityStatus state, int x, int y) :
sprite(sprite){
    this->state = state;
    this->x = x;
    this->y = y;
}

void Throwable::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

void Throwable::setState(EntityStatus state) {
    this->state = state;
}

void Throwable::render(Camera &cam) {
    if (state == RECENTLY_THROWN)
        //std::cout << "Estado viajando..\n";
        return;

    if (state == ALIVE)
        this->sprite.render(x, y, 0, cam);
}

int Throwable::getXPos() {
    return x;
}

int Throwable::getYPos() {
    return y;
}
