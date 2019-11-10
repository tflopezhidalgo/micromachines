//
// Created by eliana on 27/10/19.
//

#ifndef BOX2D_ADDHEALTHBOOSTER_H
#define BOX2D_ADDHEALTHBOOSTER_H

#include <stdlib.h>
#include "entities/Car.h"
#include "World.h"
#include "Plugin.h"

#define MAX 100

class AddHealthBooster : public Plugin {
public:
    // Agrega 2 cajas de vida en lugares random del mapa
    void updateModel(World* world, std::vector<Car*> cars) override;

    float getPosition();
};

#endif //BOX2D_ADDHEALTHBOOSTER_H
