//
// Created by leobellaera on 22/11/19.
//

#ifndef MICROMACHINES_INCREASESPEEDIFLAST_H
#define MICROMACHINES_INCREASESPEEDIFLAST_H

#include "../Plugin.h"

class IncreaseSpeedIfLast : public Plugin {
public:
    nlohmann::json updateModel(nlohmann::json& model) override;
};


#endif //MICROMACHINES_INCREASESPEEDIFLAST_H
