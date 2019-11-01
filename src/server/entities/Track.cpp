//
// Created by leobellaera on 31/10/19.
//

#include "Track.h"
#include "Car.h"

Track::Track(b2Body* body, float friction) :
    Entity(TRACK, body),
    friction(friction){}

void Track::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        car->setTiresFriction(friction);
    }
}

void Track::endCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        car->resetTiresFriction();
    }
}

void Track::setCarFriction(Car* car) {
    car->setTiresFriction(friction);
}

Track::~Track() {

}
