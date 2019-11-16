#ifndef MICROMACHINES_GRANDSTAND_H
#define MICROMACHINES_GRANDSTAND_H

#include "Box2D/Box2D.h"
#include <vector>
#include <EntitiesManager.h>
#include "Entity.h"

class Grandstand {
private:
    b2Body* body;
    int objectsThrownNumber;
    bool horizontalDisposal;
    bool positiveOrientation;
    float x_pos;
    float y_pos;
public:
    Grandstand(b2Body* body,
               int objectsThrownNumber,
               float x_pos, float y_pos,
               bool horizontalDisposal,
               bool positiveOrientation);
    void throwProjectiles(EntitiesManager& entitiesManager);
    ~Grandstand();
};

#endif //MICROMACHINES_GRANDSTAND_H
