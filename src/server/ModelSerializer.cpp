//
// Created by leobellaera on 29/10/19.
//

#include "ModelSerializer.h"

std::string ModelSerializer::serialize(std::unordered_map<std::string, Car*>& cars) {
    nlohmann::json data;
    nlohmann::json carsData = nlohmann::json::array();
    for (auto &car : cars) {
        carsData.push_back({
            car.first,
            int(round(car.second->getPosition().x) * 1000),
            int(round(car.second->getPosition().y) * 1000),
            int(round(car.second->getAngle()* 100)),
            car.second->getHealth()
        });
    }
    data["carsData"] = carsData;
    std::string dumpedData = data.dump();
    return std::move(dumpedData);
}
