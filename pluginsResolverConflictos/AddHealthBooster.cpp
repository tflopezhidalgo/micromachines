//
// Created by eliana on 9/11/19.
//

#include "AddHealthBooster.h"

float AddHealthBooster::getPosition() {
    auto val = rand() % MAX;
    float newVal = val + val % 5;
    return newVal;
}

void AddHealthBooster::updateModel(World *world, std::vector<Car *> cars) {
    world->addHealthBooster(getPosition(), getPosition());
}

extern "C" Plugin* create() {
    return new AddHealthBooster;
}
