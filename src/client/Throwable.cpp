#include "Throwable.h"

Throwable::Throwable(Throwable&& other) :
sprite(std::move(other.sprite)),
onFlySprite(std::move(other.onFlySprite)){
    this->state = other.state;
    this->x = other.x;
    this->y = other.y;
}

Throwable::Throwable(Sprite sprite, Sprite onFlySprite, EntityStatus state, int x, int y) :
sprite(sprite),
onFlySprite(onFlySprite){
    this->state = state;
    this->x = x;
    this->y = y;
}

void Throwable::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Throwable::setState(EntityStatus state) {
    this->state = state;
}

void Throwable::render(Camera &cam) {
    if (state == RECENTLY_THROWN)
        this->onFlySprite.render(x, y, 0, cam);

    if (state == ALIVE)
        this->sprite.render(x, y, 0, cam);
}

int Throwable::getXPos() {
    return x;
}

int Throwable::getYPos() {
    return y;
}
