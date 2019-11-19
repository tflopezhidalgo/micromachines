#include "Projectile.h"

#define LOWER_SPEED_LIMIT 25.f
#define PROJECTILE_FRICTION 1

Projectile::Projectile(EntityIdentifier entityIdentifier, b2Body* body, bool horizontalTrajectory) :
        Entity(entityIdentifier, body, RECENTLY_THROWN),
        body(body),
        horizontalTrajectory(horizontalTrajectory) {}

void Projectile::beginCollision(Entity* entity) {}

void Projectile::endCollision(Entity* entity) {}

void Projectile::applyForce(b2Vec2& force) {
    body->ApplyForce(force, body->GetWorldCenter(), true);
}

b2Vec2 Projectile::getForwardVelocity() {
    b2Vec2 currentForwardNormal;
    if (horizontalTrajectory) {
        currentForwardNormal = body->GetWorldVector(b2Vec2(1,0));
    } else {
        currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    }
    return b2Dot(currentForwardNormal, body->GetLinearVelocity()) * currentForwardNormal;
}

void Projectile::updateFriction() {
    b2Vec2 currentForwardNormal = getForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -PROJECTILE_FRICTION * currentForwardSpeed;
    body->ApplyForce(dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true);
}

bool Projectile::isStill() {
    float currentSpeed = body->GetLinearVelocity().Length();
    return currentSpeed < LOWER_SPEED_LIMIT;
}

Projectile::~Projectile() { }
