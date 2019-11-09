//
// Created by eliana on 9/11/19.
//

#include "AddOil.h"

void AddOil::updateModel(World *world, std::vector<Car *> cars) {
    world->addOil(getPosition(), getPosition());
}

float AddOil::getPosition() {
    auto val = rand() % MAX;
    float newVal = val + val % 5;
    return newVal;
}

extern "C" Plugin* create() {
    return static_cast<Plugin*>(new AddOil);
}
