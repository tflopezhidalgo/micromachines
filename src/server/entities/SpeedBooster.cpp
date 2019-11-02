//
// Created by eliana on 26/10/19.
//

#include "SpeedBooster.h"

SpeedBooster::SpeedBooster(
        b2Body *body,
        float speedBoost,
        float defaultMaxSpeed) :
        Entity(SPEEDBOOSTER, body),
        defaultMaxForwardSpeed(defaultMaxSpeed),
        speedBoost(speedBoost) {}

void SpeedBooster::beginCollision(Entity *entity) {
    //todo
}

void SpeedBooster::endCollision(Entity *entity) {}
