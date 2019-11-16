#include "Entity.h"

Entity::Entity(EntityIdentifier identifier, b2Body* body, EntityStatus entityStatus) :
    identifier(identifier),
    body(body),
    status(entityStatus) {}

EntityIdentifier Entity::getIdentifier() {
    return identifier;
}

b2Vec2 Entity::getPosition() {
    return body->GetPosition();
}

float Entity::getAngle() {
    return body->GetAngle();
}

EntityStatus Entity::getStatus() {
    return status;
}

bool Entity::isDead() {
    return status == DEAD;
}

void Entity::die() {
    status = DEAD;
}

void Entity::move(b2Vec2 position, float angle) {
    body->SetLinearVelocity({0,0});
    body->SetAngularVelocity(0);
    body->SetTransform(position, angle);
}

Entity::~Entity() {
    body->GetWorld()->DestroyBody(body);
}
