//
// Created by leobellaera on 22/11/19.
//

#ifndef MICROMACHINES_DELETEMUDZONES_H
#define MICROMACHINES_DELETEMUDZONES_H

#include "../Plugin.h"

class DeleteMudZones : public Plugin {
        public:
        nlohmann::json updateModel(nlohmann::json& model) override;
};


#endif //MICROMACHINES_DELETEMUDZONES_H
