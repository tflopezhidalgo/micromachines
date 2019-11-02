//
// Created by leobellaera on 24/10/19.
//

#ifndef TESTING_HEALTHBOOSTER_H
#define TESTING_HEALTHBOOSTER_H

#include "Entity.h"
#include "Car.h"

class HealthBooster : public Entity {
private:
    int healthBoost;
public:
    explicit HealthBooster(b2Body* body, int healing);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void heal(Car* car);
};

#endif //TESTING_HEALTHBOOSTER_H
