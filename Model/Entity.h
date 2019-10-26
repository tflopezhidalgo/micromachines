//
// Created by eliana on 19/10/19.
//

#ifndef TESTING_ENTITY_H
#define TESTING_ENTITY_H

#include "Box2D/Box2D.h"

enum Status {
    ALIVE,
    SEVERALDAMAGED,
    DEAD
};

enum Identifier {
    CAR,
    HEALTHBOOSTER,
    OIL,
    SPEEDBOOSTER,
    STONE,
    MUD,
};

class Entity {
private:
    Identifier identifier;
    b2Body* body;
    Status status;
public:
    Entity(Identifier identifier, b2Body* body);
    virtual void collide(Entity* entity) = 0;
    b2Vec2 getPosition();
    float getAngle();
    Identifier getIdentifier();
    ~Entity();
    virtual void collideEnd(Entity* entity) = 0;
    Status getStatus();
};

#endif //TESTING_ENTITY_H
