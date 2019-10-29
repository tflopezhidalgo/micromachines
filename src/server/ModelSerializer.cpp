//
// Created by leobellaera on 29/10/19.
//

#include "ModelSerializer.h"

std::string ModelSerializer::serialize(std::unordered_map<std::string, Car*>& cars) {
    nlohmann::json data;
    for (auto &car : cars) {
        data[car.first] = {car.second->getPosition().x, car.second->getPosition().y, car.second->getAngle()};
    }
    std::string dumpedData = data.dump();
    return std::move(dumpedData);
}
