//
// Created by leobellaera on 15/11/19.
//

#include "DecreaseSpeedIfDamaged.h"

#define SEVERAL_DAMAGED_HEALTH 50
#define DAMAGED_FORWARD_SPEED -150.f

nlohmann::json DecreaseSpeedIfDamaged::updateModel(nlohmann::json& model) {

    nlohmann::json requests;

    std::vector<std::tuple<std::string, float, int, int>> carsModifications;

    for (auto & carData : model["carsData"]) {
        std::string carId = carData[CAR_DATA_ID_IDX].get<std::string>();
        auto health = carData[CAR_DATA_HEALTH_IDX].get<int>();
        if (health < SEVERAL_DAMAGED_HEALTH && health > 0) {
            carsModifications.emplace_back(std::make_tuple(carId, DAMAGED_FORWARD_SPEED, 0, 0));
        }
    }

    addCarsModifications(requests, carsModifications);
    return std::move(requests);
}

extern "C" Plugin* create() {
    return new DecreaseSpeedIfDamaged;
}
