//
// Created by eliana on 20/10/19.
//

#ifndef TESTING_OIL_H
#define TESTING_OIL_H

#include "Entity.h"
#include "Car.h"

class Oil : public Entity {
private:
    float friction;
    float initialFriction;
public:
    Oil(b2Body *body, float initialFriction, float friction);
    void collide(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void setFriction(Car *car);
    void resetFriction(Car *car);
};


#endif //TESTING_OIL_H
