//
// Created by eliana on 26/10/19.
//

#ifndef TESTING_SPEEDBOOSTER_H
#define TESTING_SPEEDBOOSTER_H

#include "Car.h"
#include "Entity.h"
#include <map>

class SpeedBooster : public Entity {
private:
    float initialMaxSpeed;
    float speedBoost;
public:
    SpeedBooster(b2Body *body, std::map<std::string, float>& config);
    void collide(Entity* entity) override;
    void endCollision(Entity* entity) override;
};


#endif //TESTING_SPEEDBOOSTER_H

