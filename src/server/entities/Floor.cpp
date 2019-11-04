//
// Created by leobellaera on 31/10/19.
//

#include "Floor.h"
#include "Car.h"

Floor::Floor(b2Body* body, float friction) :
    Entity(TRACK, body),
    friction(friction){}

void Floor::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        car->setTiresFriction(friction);
    }
}

void Floor::endCollision(Entity* entity) {

}

void Floor::setCarFriction(Car* car) {
    car->setTiresFriction(friction);
}

Floor::~Floor() {}
