//
// Created by leobellaera on 31/10/19.
//

#ifndef MICROMACHINES_TRACK_H
#define MICROMACHINES_TRACK_H

#include "Box2D/Box2D.h"
#include "Entity.h"
#include "Car.h"

enum Shape {
    HORIZONTAL,
    VERTICAL,
    //curved shapes
};

class Track : public Entity {
private:
    float friction;
public:
    Track(b2Body* body, float friction);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void setCarFriction(Car* car);
    ~Track();
};

#endif //MICROMACHINES_TRACK_H
