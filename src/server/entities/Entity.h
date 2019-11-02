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
    TRACK
};

class Entity {
private:
    Identifier identifier;
    b2Body* body;
    Status status;
public:
    Entity(Identifier identifier, b2Body* body);
    virtual void beginCollision(Entity* entity) = 0;
    virtual void endCollision(Entity* entity) = 0;
    b2Vec2 getPosition();
    float getAngle();
    Status getStatus();
    Identifier getIdentifier();
    bool isDead();
    void die();
    b2Body* getBody();
    ~Entity();

    void receiveSeveralDamage();
};

#endif //TESTING_ENTITY_H
