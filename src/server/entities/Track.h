//
// Created by leobellaera on 31/10/19.
//

#ifndef MICROMACHINES_STRAIGHTTRACK_H
#define MICROMACHINES_STRAIGHTTRACK_H

#include "Box2D/Box2D.h"
#include "Entity.h"
#include "Car.h"

class StraightTrack : public Entity {
private:
    float friction;
public:
    StraightTrack(b2Body* body, float friction);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void setCarFriction(Car* car);
    ~StraightTrack();
};

#endif //MICROMACHINES_STRAIGHTTRACK_H
