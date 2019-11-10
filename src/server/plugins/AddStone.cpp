//
// Created by eliana on 9/11/19.
//

#include "AddStone.h"

void AddStone::updateModel(World* world, std::vector<Car*> cars) {
    world->addStone(getPosition(), getPosition());
}

float AddStone::getPosition() {
    auto val = rand() % MAX;
    float newVal = val + val % 5;
    return newVal;
}

extern "C" Plugin* create() {
    return new AddStone;
}
