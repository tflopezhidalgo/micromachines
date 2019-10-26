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
    float friction;
    float startFriction;
public:
    Oil(Identifier identifier, b2Body *body, std::map<std::string, float>& config);
    void collide(Entity* entity) override;
    void collideEnd(Entity* entity) override;
    void setFriction(Car *car);
    void resetFriction(Car *car);
};


#endif //TESTING_OIL_H
