//
// Created by leobellaera on 10/11/19.
//

#include "Grass.h"

Grass::Grass(b2Body* body, float friction) :
        Entity(GRASS, body),
        friction(friction) {}

void Grass::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        setCarFriction(car);
        updateCarSurface(car);
    }
}

void Grass::endCollision(Entity* entity) {}

void Grass::setCarFriction(Car* car) {
    car->setTiresFriction(friction);
}

void Grass::updateCarSurface(Car* car) {
    car->updateSurface(GRASS);
}

Grass::~Grass() {}
