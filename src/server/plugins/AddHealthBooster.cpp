//
// Created by eliana on 27/10/19.
//

#ifndef BOX2D_ADDHEALTHBOOSTER_H
#define BOX2D_ADDHEALTHBOOSTER_H

#include <stdlib.h>
#include "entities/Car.h"
#include "entities/World.h"

#define MAX 100

class AddHealthBooster {
public:
    // Agrega 2 cajas de vida en lugares random del mapa
    void updateModel(std::vector<Car*> cars, World* world) {
        world->addHealthBooster(getPosition(), getPosition());
    }

    float getPosition() {
        auto val = rand() % MAX;
        float newVal = val + val % 5;
        return newVal;
    }
};

#endif //BOX2D_ADDHEALTHBOOSTER_H
