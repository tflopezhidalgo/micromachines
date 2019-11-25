#include "StaticObject.h"

StaticObject::StaticObject(Sprite sprite) :
sprite(sprite), x(0), y(0), angle(0) { }

void StaticObject::setPosition(int x, int y, int angle) {
    this->x = x;
    this->y = y;
    this->angle = angle;
}

void StaticObject::render(Camera &camera) {
    this->sprite.render(x, y, angle, camera);
}

void StaticObject::setState(EntityStatus state){

}

int StaticObject::getYPos() {
    return y;
}

int StaticObject::getXPos() {
    return x;
}
