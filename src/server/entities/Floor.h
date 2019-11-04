//
// Created by leobellaera on 31/10/19.
//

#ifndef MICROMACHINES_FLOOR_H
#define MICROMACHINES_FLOOR_H

#include "Box2D/Box2D.h"
#include "Entity.h"
#include "Car.h"

//todo curved shapes
class Floor : public Entity {
private:
    float friction;
public:
    Floor(b2Body* body, float friction);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void setCarFriction(Car* car);
    ~Floor();
};

#endif //MICROMACHINES_FLOOR_H
