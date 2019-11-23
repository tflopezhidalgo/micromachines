#include "StaticObject.h"

StaticObject::StaticObject(Sprite sprite) :
sprite(sprite), x(0), y(0) { }

void StaticObject::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void StaticObject::render(Camera &camera) {
    this->sprite.render(x, y, 0, camera);
}

void StaticObject::setState(EntityStatus state){

}

int StaticObject::getYPos() {
    return y;
}

int StaticObject::getXPos() {
    return x;
}
