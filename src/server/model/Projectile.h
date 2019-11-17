#ifndef MICROMACHINES_PROJECTILE_H
#define MICROMACHINES_PROJECTILE_H

#include <Identifiers.h>
#include <Box2D/Box2D.h>
#include "Entity.h"

class Projectile : public Entity {
private:
    b2Body* body;
    b2Vec2 getForwardVelocity();
public:
    Projectile(EntityIdentifier entityIdentifier, b2Body* body);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void updateFriction();
    void applyForce(b2Vec2& impulse);
    bool isStill();
    ~Projectile();
};


#endif //MICROMACHINES_PROJECTILE_H
