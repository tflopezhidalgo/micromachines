#ifndef MICROMACHINES_PROJECTILE_H
#define MICROMACHINES_PROJECTILE_H

#include <Identifiers.h>
#include <Box2D/Box2D.h>
#include "Entity.h"

class Projectile : public Entity {
private:
    b2Body* body;
    b2Vec2 getForwardVelocity();
    bool horizontalTrajectory;
public:
    Projectile(EntityIdentifier entityIdentifier, b2Body* body, bool horizontalTrajectory);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void updateFriction();
    void applyForce(b2Vec2& force);
    bool isStill();
    ~Projectile();
};


#endif //MICROMACHINES_PROJECTILE_H
