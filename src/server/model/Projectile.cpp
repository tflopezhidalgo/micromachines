//
// Created by leobellaera on 6/11/19.
//

#include "Projectile.h"

#define LOWER_SPEED_LIMIT 1.f
#define PROJECTILE_FRICTION 1

Projectile::Projectile(EntityIdentifier entityIdentifier, b2Body* body) :
    Entity(entityIdentifier, body, RECENTLY_THROWN),
    body(body) {}

void Projectile::beginCollision(Entity* entity) {}

void Projectile::endCollision(Entity* entity) {}

void Projectile::applyLinearImpulse(b2Vec2& impulse) {
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
}

b2Vec2 Projectile::getForwardVelocity() {
    b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    return b2Dot(currentForwardNormal, body->GetLinearVelocity()) * currentForwardNormal;
}

void Projectile::updateFriction() {
    b2Vec2 currentForwardNormal = getForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -PROJECTILE_FRICTION * currentForwardSpeed;
    body->ApplyForce(dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true);
}

bool Projectile::isStill() {
    b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    float velocityNorm = (b2Dot(currentForwardNormal, body->GetLinearVelocity()) * currentForwardNormal).Length();
    return velocityNorm < LOWER_SPEED_LIMIT;
}

Projectile::~Projectile() { }
