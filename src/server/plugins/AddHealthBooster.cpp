//
// Created by eliana on 27/10/19.
//

#ifndef BOX2D_ADDHEALTHBOOSTER_H
#define BOX2D_ADDHEALTHBOOSTER_H

#include <stdlib.h>
#include "Plugin.h"
#include "entities/Car.h"
#include "entities/World.h"

class AddHealthBooster : public Plugin {
public:
    // Agrega 2 cajas de vida en lugares random del mapa
    void updateModel(std::vector<Car*> cars, World* world) {
        world->addHealthBooster(rand() % 100, rand() % 100);
        world->addHealthBooster(rand() % 100, rand() % 100);
    }
};

#endif //BOX2D_ADDHEALTHBOOSTER_H
