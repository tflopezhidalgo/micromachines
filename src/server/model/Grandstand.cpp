#include "Grandstand.h"
#include "Constants.h"
#include "Identifiers.h"

#define THROWABLE_OBJECTS_NUMBER 5
#define MAX_FORCE 15000
#define MIN_FORCE 1000
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

        float randForce = MIN_FORCE + static_cast<float>(rand()) /
                (static_cast<float>(float(RAND_MAX)/(MAX_FORCE - MIN_FORCE)));

        b2Vec2 force;

        if (horizontalDisposal) {
            if (positiveOrientation) {
                force = {0, randForce};
            } else {
                force = {0, -randForce};
            }
        } else {
            if (positiveOrientation) {
                force = {randForce, 0};
            } else {
                force = {-randForce, 0};
            }
        }

        entitiesManager.addProjectile(entityIdentifier, xPos, yPos, force);
    }

}

Grandstand::~Grandstand() {
    body->GetWorld()->DestroyBody(body);
}
