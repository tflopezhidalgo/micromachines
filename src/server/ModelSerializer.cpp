//
// Created by leobellaera on 29/10/19.
//

#include "ModelSerializer.h"
#include "Macros.h"

std::string ModelSerializer::serialize(std::unordered_map<std::string, Car*>& cars) {
    nlohmann::json data;
    nlohmann::json carsData = nlohmann::json::array();
    for (auto &car : cars) {
        carsData.push_back({
            car.first,
            int(car.second->getPosition().x * SERIALIZING_RESCAILING),
            int(car.second->getPosition().y * SERIALIZING_RESCAILING),
            int(car.second->getAngle()* SERIALIZING_RESCAILING),
            car.second->getHealth()
        });
    }
    data["carsData"] = carsData;
    std::string dumpedData = data.dump();
    return std::move(dumpedData);
}
