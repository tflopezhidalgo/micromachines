//
// Created by leobellaera on 29/10/19.
//

#include "StatusSerializer.h"
#include "Constants.h"

std::string StatusSerializer::serialize(RaceJudge& raceJudge,
                                        std::unordered_map<std::string, Car*>& cars,
                                        std::unordered_map<int, Entity*>& entities) {
    nlohmann::json data;
    nlohmann::json carsData = nlohmann::json::array();
    for (auto &car : cars) {
        std::string carId = car.first;
        carsData.push_back({
            carId,
            int(car.second->getPosition().x * SERIALIZING_RESCAILING),
            int(car.second->getPosition().y * SERIALIZING_RESCAILING),
            int(car.second->getAngle()* SERIALIZING_RESCAILING),
            car.second->getHealth(),
            raceJudge.getLapsDone(carId)
        });
    }
    data["carsData"] = carsData;

    nlohmann::json entitiesData = nlohmann::json::array();
    for (auto &entity : entities) {
        entitiesData.push_back({
            entity.first,
            entity.second->getIdentifier(),
            entity.second->getStatus(),
            int(entity.second->getPosition().x * SERIALIZING_RESCAILING),
            int(entity.second->getPosition().y * SERIALIZING_RESCAILING),
        });
    }
    data["entitiesData"] = entitiesData;

    data["carsArrivalOrder"] = raceJudge.getCarsArrivalOrder();

    std::string dumpedData = data.dump();
    return std::move(dumpedData);
}
