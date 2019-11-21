//
// Created by leobellaera on 15/11/19.
//

#include "DecreaseSpeedIfDamaged.h"

#define SEVERAL_DAMAGED_HEALTH 50
#define DAMAGED_FORWARD_SPEED -150.f

nlohmann::json DecreaseSpeedIfDamaged::updateModel(nlohmann::json& model) {

    nlohmann::json requests;
    nlohmann::json carsModifications = nlohmann::json::array();

    for (auto & carData : model["carsData"]) {
        std::string carId = carData[0].get<std::string>();
        auto health = carData[1].get<int>();
        if (health < SEVERAL_DAMAGED_HEALTH) {
            carsModifications.push_back({
                carId,
                DAMAGED_FORWARD_SPEED,
            });
        }
    }

    requests["carsModifications"] = carsModifications;
    return std::move(requests);
}

extern "C" Plugin* create() {
    return new DecreaseSpeedIfDamaged;
}
