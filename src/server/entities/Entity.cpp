//
// Created by eliana on 19/10/19.
//

#include "Entity.h"

Entity::Entity(Identifier identifier, b2Body* body) :
    identifier(identifier),
    body(body),
    status(Status::ALIVE) {}

Identifier Entity::getIdentifier() {
    return identifier;
}

b2Vec2 Entity::getPosition() {
    return body->GetPosition();
}

float Entity::getAngle() {
    return body->GetAngle();
}

Status Entity::getStatus() {
    return status;
}

bool Entity::isDead() {
    return status == DEAD;
}

void Entity::die() {
    status = DEAD;
}

void Entity::receiveSeveralDamage() {
    status = SEVERALDAMAGED;
}

b2Body* Entity::getBody() {
    return body;
}

Entity::~Entity() {
    body->GetWorld()->DestroyBody(body);
}
