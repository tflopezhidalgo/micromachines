//
// Created by eliana on 20/10/19.
//

#include "Oil.h"

Oil::Oil(b2Body *body, float grip, std::vector<TimedEvent>& timedEvents) :
        Entity(OIL, body),
        timedEvents(timedEvents),
        grip(grip) {}

void Oil::beginCollision(Entity *entity) {
    if (entity->getIdentifier() == CAR && !isDead()) {
        Car* car = dynamic_cast<Car*>(entity);
        //todo
        die();
    }
}

void Oil::endCollision(Entity *entity) {}

Oil::~Oil() {}
