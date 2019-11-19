#ifndef MICROMACHINES_GRANDSTAND_H
#define MICROMACHINES_GRANDSTAND_H

#include "Box2D/Box2D.h"
#include <vector>
#include <EntitiesManager.h>
#include "Entity.h"

class Grandstand : public Entity {
private:
    int objectsThrownNumber;
    bool horizontalDisposal;
    bool positiveOrientation;
    float x_pos;
    float y_pos;
    std::vector<TimedEvent> &timedEvents;
public:
    Grandstand(
            b2Body* body,
            int objectsThrownNumber,
            float x_pos, float y_pos,
            bool horizontalDisposal,
            bool positiveOrientation,
            std::vector<TimedEvent> &timedEvents);

    void throwProjectiles(EntitiesManager& entitiesManager);

    void beginCollision(Entity* entity) override;

    void endCollision(Entity* entity) override;

    void damageCar(Car* car);

    ~Grandstand();
};

#endif //MICROMACHINES_GRANDSTAND_H
