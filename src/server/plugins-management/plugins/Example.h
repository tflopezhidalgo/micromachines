//
// Created by leobellaera on 13/11/19.
//

#ifndef MICROMACHINES_EXAMPLE_H
#define MICROMACHINES_EXAMPLE_H

#include "../Plugin.h"

class Example : public Plugin {
    void updateModel(EntitiesManager& entitiesManager,
                     std::unordered_map<std::string, Car*> cars,
                     RaceJudge& raceJudge) override;
};

#endif //MICROMACHINES_EXAMPLE_H
