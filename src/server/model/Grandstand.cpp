#include "Grandstand.h"
#include "Constants.h"
#include "Identifiers.h"

#define THROWABLE_OBJECTS_NUMBER 5
#define MAX_FORCE 5000
#define MIN_FORCE 3000
#define PROJECTILE_INITIAL_DISTANCE 0.5f

Grandstand::Grandstand(b2Body* body, int objectsThrownNumber, float x_pos,
        float y_pos, bool horizontalDisposal, bool positiveOrientation,
        std::vector<TimedEvent> &timedEvents) :

    timedEvents(timedEvents),
    Entity(GRANDSTAND, body),
    objectsThrownNumber(objectsThrownNumber),
    horizontalDisposal(horizontalDisposal),
    positiveOrientation(positiveOrientation),
    x_pos(x_pos),
    y_pos(y_pos) {

    body->SetUserData(this);

}

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
            if (!positiveOrientation) {
                yPos = yPos * -1;
            }
        } else {
            lo = y_pos - float(GRANDSTAND_WIDTH)/2;
            hi = y_pos + float(GRANDSTAND_WIDTH)/2;
            xPos = x_pos + GRANDSTAND_HEIGHT/2.f + PROJECTILE_INITIAL_DISTANCE;
            yPos = lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(hi-lo)));
            if (!positiveOrientation) {
                xPos = xPos * -1;
            }
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
                force = {randForce, 150};
            } else {
                force = {-randForce, 150};
            }
        }
        entitiesManager.addProjectile(entityIdentifier, xPos, yPos, force, !horizontalDisposal);
    }

}

void Grandstand::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        damageCar(car);
    }
}

void Grandstand::endCollision(Entity* entity) {}

void Grandstand::damageCar(Car* car) {
    if (car->getSpeed() < 70) {
        return;
    }
    car->receiveDamage(40);
    if (car->isDead()) {
        car->resetMaxForwardSpeed();
        timedEvents.emplace_back(TimedEvent(car, &Car::updatePosition, 1.5f));
        timedEvents.emplace_back(TimedEvent(car, &Car::recoverHealth, 1.5f));
    }
}

Grandstand::~Grandstand() {}
