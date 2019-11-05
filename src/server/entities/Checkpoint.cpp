//
// Created by leobellaera on 4/11/19.
//

#include "Checkpoint.h"
#include "Identifiers.h"

Checkpoint::Checkpoint(b2Body* body, int checkpointOrder, RaceJudge& raceJudge) :
        Entity(CHECKPOINT, body),
        order(checkpointOrder),
        raceJudge(raceJudge) {}

void Checkpoint::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        Car* car = dynamic_cast<Car*>(entity);
        activate(car);
    }
}

void Checkpoint::endCollision(Entity* entity) {}

void Checkpoint::activate(Car* car) {
    raceJudge.activate(car->getId(), order);
}

Checkpoint::~Checkpoint() {}
