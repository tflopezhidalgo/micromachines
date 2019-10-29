//
// Created by eliana on 26/10/19.
//

#include "SpeedBooster.h"


SpeedBooster::SpeedBooster(b2Body *body, float initialMaxSpeed, float speedBoost) :
        Entity(SPEEDBOOSTER, body),
        initialMaxSpeed(initialMaxSpeed),
        speedBoost(speedBoost) {}

void SpeedBooster::collide(Entity *entity) {
    // time
    // updateMaxForwardVelocity
    this->exploit();
}

void SpeedBooster::endCollision(Entity *entity) {
    this->die();
}
