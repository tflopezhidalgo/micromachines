//
// Created by leobellaera on 3/11/19.
//

#include "Grandstand.h"
#include "Constants.h"
#include "Identifiers.h"

#define THROWABLE_OBJECTS_NUMBER 5
#define MAX_LINEAR_IMPULSE 20
#define MIN_LINEAR_IMPULSE 10
#define PROJECTILE_INITIAL_DISTANCE 0.5f

Grandstand::Grandstand(b2Body* body, int objectsThrownNumber, float x_pos,
        float y_pos, bool horizontalDisposal, bool positiveOrientation) :
    body(body),
    objectsThrownNumber(objectsThrownNumber),
    horizontalDisposal(horizontalDisposal),
    positiveOrientation(positiveOrientation),
    x_pos(x_pos),
    y_pos(y_pos) {}

void Grandstand::throwProjectiles(EntitiesManager& entitiesManager) {
    EntityIdentifier projectiles[5] = {HEALTHBOOSTER, OIL, SPEEDBOOSTER, STONE, MUD};

    for (int i = 0; i < objectsThrownNumber; i++) {

        int randIdx = rand() % THROWABLE_OBJECTS_NUMBER;
        EntityIdentifier entityIdentifier = projectiles[randIdx];

        float xPos, yPos, hi, lo;
        if (horizontalDisposal) {
            lo = x_pos - float(GRANDSTAND_WIDTH)/2;
            hi = x_pos + float(GRANDSTAND_WIDTH)/2;
            xPos = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(hi-lo)));
            yPos = y_pos + GRANDSTAND_HEIGHT/2.f + PROJECTILE_INITIAL_DISTANCE;
        } else {
            lo = y_pos - float(GRANDSTAND_WIDTH)/2;
            hi = y_pos + float(GRANDSTAND_WIDTH)/2;
            xPos = x_pos + GRANDSTAND_HEIGHT/2.f + PROJECTILE_INITIAL_DISTANCE;
            yPos = lo + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(hi-lo)));
        }

        float randLinearImpulse = MIN_LINEAR_IMPULSE + static_cast<float>(rand()) /
                (static_cast<float>(float(RAND_MAX)/(MAX_LINEAR_IMPULSE - MIN_LINEAR_IMPULSE)));
        b2Vec2 linearImpulse = {0,3}; //todo apply impulse

        entitiesManager.addProjectile(entityIdentifier, xPos, yPos, linearImpulse);
    }

}

Grandstand::~Grandstand() {
    body->GetWorld()->DestroyBody(body);
}
