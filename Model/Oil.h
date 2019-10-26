//
// Created by eliana on 20/10/19.
//

#ifndef TESTING_OIL_H
#define TESTING_OIL_H

#include "Entity.h"
#include "Car.h"

class Oil : public Entity {
private:
    b2Body* body;
    int friction;
    float prevFriction;
public:
    Oil(Identifier identifier, b2Body *body);
    void collide(Entity* entity) override;
    void collideEnd(Entity* entity) override;
    void setFriction(Car *car);
    void resetFriction(Car *car);
};


#endif //TESTING_OIL_H
