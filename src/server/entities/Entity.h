//
// Created by eliana on 19/10/19.
//

#ifndef TESTING_ENTITY_H
#define TESTING_ENTITY_H

#include "Box2D/Box2D.h"
#include "Identifiers.h"

class Entity {
private:
    EntityIdentifier identifier;
    b2Body* body;
    EntityStatus status;
public:
    Entity(EntityIdentifier identifier, b2Body* body, EntityStatus entityStatus = ALIVE);
    virtual void beginCollision(Entity* entity) = 0;
    virtual void endCollision(Entity* entity) = 0;
    b2Vec2 getPosition();
    float getAngle();
    EntityStatus getStatus();
    EntityIdentifier getIdentifier();
    bool isDead();
    void die();
    virtual ~Entity();
};

#endif //TESTING_ENTITY_H
