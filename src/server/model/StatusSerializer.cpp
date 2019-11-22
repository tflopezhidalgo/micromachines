#include "StatusSerializer.h"
#include "Constants.h"

std::string StatusSerializer::getClientsModelSerialization(
        RaceJudge& raceJudge,
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
            int(car.second->getAngle() * SERIALIZING_RESCAILING),
            car.second->getHealth(),
            raceJudge.getLapsDone(carId),
            car.second->hasReducedVision()
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
    data["matchFinished"] = raceJudge.raceFinished();

    return std::move(data.dump());
}

nlohmann::json StatusSerializer::getPluginsModelSerialization(
        RaceJudge& raceJudge,
        std::unordered_map<std::string, Car*>& cars,
        std::unordered_map<int, Entity*>& entities) {

    nlohmann::json data;

    nlohmann::json carsData = nlohmann::json::array();

    for (auto &car : cars) {
        std::string carId = car.first;
        carsData.push_back({
            carId,
            car.second->getPosition().x,
            car.second->getPosition().y,
            car.second->getHealth(),
            raceJudge.getCheckpointsTaken(carId),
            raceJudge.getLapsDone(carId)
        });
    }

    data["carsData"] = carsData;

    nlohmann::json entitiesData = nlohmann::json::array();

    for (auto & entity : entities) {
        int id = entity.first;
        entitiesData.push_back({
            id,
            entity.second->getIdentifier(),
            entity.second->getPosition().x,
            entity.second->getPosition().y
            });
    }

    data["entitiesData"] = entitiesData;

    return std::move(data);
}
