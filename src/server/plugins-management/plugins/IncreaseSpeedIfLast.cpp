//
// Created by leobellaera on 22/11/19.
//

#include "IncreaseSpeedIfLast.h"

#define SPEED_BOOST 80.f

nlohmann::json IncreaseSpeedIfLast::updateModel(nlohmann::json& model) {

    nlohmann::json requests;

    std::vector<std::tuple<std::string, float, int, int>> carsModifications;

    if (model["carsData"].size() < 2) {
        return requests;
    }

    bool increase = false;
    std::string carId =  model["carsData"][0][CAR_DATA_ID_IDX];
    int checkpointsTaken = model["carsData"][0][CAR_DATA_CHECKPOINTS_IDX];

    for (auto & carData : model["carsData"]) {
        std::string actualCarId = carData[CAR_DATA_ID_IDX].get<std::string>();
        int actualCheckpointsTaken = carData[CAR_DATA_HEALTH_IDX].get<int>();
        if (actualCheckpointsTaken < checkpointsTaken) {
            increase = true;
            carId = actualCarId;
            checkpointsTaken = actualCheckpointsTaken;
        }
    }

    if (increase) {
        carsModifications.emplace_back(std::make_tuple(carId, SPEED_BOOST, 0, 0));
        addCarsModifications(requests, carsModifications);
    }

    return std::move(requests);
}

extern "C" Plugin* create() {
    return new IncreaseSpeedIfLast;
}