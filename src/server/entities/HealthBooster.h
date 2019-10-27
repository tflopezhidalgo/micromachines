//
// Created by leobellaera on 24/10/19.
//

#ifndef TESTING_HEALTHBOOSTER_H
#define TESTING_HEALTHBOOSTER_H

#include "../Box2D/Box2D.h"
#include "Entity.h"
#include "Car.h"

class HealthBooster : public Entity {
private:
    int healthBoost;
public:
    explicit HealthBooster(b2Body* body);
    void collide(Entity* entity) override;
    void collideEnd(Entity* entity) override;
    void boost(Car* car);
};

#endif //TESTING_HEALTHBOOSTER_H
