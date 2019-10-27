//
// Created by eliana on 26/10/19.
//

#include "SpeedBooster.h"
#define STARTSPEED "maxForwardSpeed"
#define BOOSTERSPEED "boosterSpeed"

SpeedBooster::SpeedBooster(Identifier identifier,
        b2Body *body, std::map<std::string, float> &config) :
    Entity(SPEEDBOOSTER, body),
    startSpeed(config.find(STARTSPEED)->second),
    speed(config.find(BOOSTERSPEED)->second) {}

void SpeedBooster::collide(Entity *entity) {

}

void SpeedBooster::collideEnd(Entity *entity) {

}
