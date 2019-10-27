//
// Created by eliana on 26/10/19.
//

#ifndef TESTING_SPEEDBOOSTER_H
#define TESTING_SPEEDBOOSTER_H

#include "Car.h"
#include "Entity.h"
#include <map>

class SpeedBooster : public Entity {
public:
    b2Body* body;
    float startSpeed;
    float speed;
private:
    SpeedBooster(Identifier identifier, b2Body *body, std::map<std::string, float>& config);
    void collide(Entity* entity) override;
    void collideEnd(Entity* entity) override;
};


#endif //TESTING_SPEEDBOOSTER_H
