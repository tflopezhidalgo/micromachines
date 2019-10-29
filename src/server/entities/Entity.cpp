//
// Created by eliana on 19/10/19.
//

#include "Entity.h"

Entity::Entity(Identifier identifier, b2Body* body) :
    identifier(identifier),
    body(body),
    status(ALIVE) {}

Identifier Entity::getIdentifier() {
    return identifier;
}

b2Vec2 Entity::getPosition() {
    return body->GetPosition();
}

float Entity::getAngle() {
    return body->GetAngle();
}

void Entity::exploit() {
    status = EXPLOITED;
}

void Entity::die() {
    status = DEAD;
}

Status Entity::getStatus() {
    return status;
}

Entity::~Entity() {}
