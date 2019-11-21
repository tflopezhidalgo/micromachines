//
// Created by leobellaera on 15/11/19.
//

#ifndef MICROMACHINES_DECREASESPEEDIFDAMAGED_H
#define MICROMACHINES_DECREASESPEEDIFDAMAGED_H


#include "../Plugin.h"

class DecreaseSpeedIfDamaged : public Plugin {
public:
    nlohmann::json updateModel(nlohmann::json& model) override;
};

#endif //MICROMACHINES_DECREASESPEEDIFDAMAGED_H
