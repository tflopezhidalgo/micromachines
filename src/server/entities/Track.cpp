//
// Created by leobellaera on 31/10/19.
//

#include <iostream>
#include "Track.h"
#include "Car.h"

Track::Track(b2Body* body, b2Vec2 position, int floorId, float friction) :
    Entity(TRACK, body),
    friction(friction),
    position(position) {

    if (floorId == LEFT_TRACK || floorId == LEFT_CHECKPOINTED_TRACK) {
        angle = 90;

    } else if (floorId == RIGHT_TRACK || floorId == RIGHT_CHECKPOINTED_TRACK) {
        angle = -90;

    } else if (floorId == UP_TRACK || floorId == UP_CHECKPOINTED_TRACK ||
        floorId == SECOND_QUAD_TRACK || floorId == THIRD_QUAD_TRACK) {
        angle = 180;

    } else if (floorId == DOWN_TRACK || floorId == DOWN_CHECKPOINTED_TRACK ||
        floorId == FIRST_QUAD_TRACK || floorId == FOURTH_QUAD_TRACK) {
        angle = 0;
    }
}

void Track::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        setCarFriction(car);
        updateCarSurface(car);
    }
}

void Track::endCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        updateRespawnData(car);
    }
}

void Track::updateRespawnData(Car* car) {
    car->setLastPosOnTrack(car->getPosition());
    car->setRespawnCoordinates(position, angle);
}

void Track::setCarFriction(Car* car) {
    car->setTiresFriction(friction);
}

void Track::updateCarSurface(Car* car) {
    car->updateSurface(TRACK);
}

Track::~Track() {}
