//
// Created by eliana on 26/10/19.
//

#include "SpeedBooster.h"

#define INITIAL_MAX_SPEED "maxForwardSpeed"
#define SPEED_BOOST "speedBoost"

SpeedBooster::SpeedBooster(
        b2Body *body, std::map<std::string, float> &config) :
        Entity(SPEEDBOOSTER, body),
        initialMaxSpeed(config.find(INITIAL_MAX_SPEED)->second),
        speedBoost(config.find(SPEED_BOOST)->second) {}

void SpeedBooster::collide(Entity *entity) {

}

void SpeedBooster::endCollision(Entity *entity) {

}
