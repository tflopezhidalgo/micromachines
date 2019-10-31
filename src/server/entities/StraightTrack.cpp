//
// Created by leobellaera on 31/10/19.
//

#include "StraightTrack.h"
#include "Car.h"

StraightTrack::StraightTrack(b2Body* body, float friction) :
    Entity(STRAIGHT_TRACK, body),
    friction(friction){}

void StraightTrack::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        car->setTiresFriction(friction);
    }
}

void StraightTrack::endCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        car->resetTiresFriction();
    }
}

void StraightTrack::setCarFriction(Car* car) {
    car->setTiresFriction(friction);
}

StraightTrack::~StraightTrack() {

}
