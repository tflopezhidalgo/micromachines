//
// Created by leobellaera on 20/11/19.
//

#include "PluginRequestsProcessor.h"
#include "PluginsConstants.h"

PluginRequestsProcessor::PluginRequestsProcessor
        (EntitiesManager& entitiesManager,
        std::unordered_map<std::string, Car*>& cars) :
        entitiesManager(entitiesManager),
        cars(cars) {}

void PluginRequestsProcessor::process(nlohmann::json& pluginRequests) {

    if (pluginRequests.is_null()) {
        return;
    }

    for (auto& entity : pluginRequests[ENTITIES_ADDITIONS_KEY]) {
        auto identifier = entity[ENTITY_IDENTIFIER_IDX].get<EntityIdentifier>();
        auto x_pos = entity[ENTITY_INITIAL_X_POS_IDX].get<float>();
        auto y_pos = entity[ENTITY_INITIAL_Y_POS_IDX].get<float>();
        entitiesManager.addEntity(identifier, x_pos, y_pos);
    }

    for (auto & entityId : pluginRequests[ENTITIES_DELETIONS_KEY]) {
        entitiesManager.deleteEntity(entityId);
    }

    for (auto & carModification : pluginRequests[CARS_MODIFICATIONS_KEY]) {
        auto carId = carModification[CAR_ID_IDX].get<std::string>();
        Car* car = cars.find(carId)->second;

        auto forwardSpeedDiff = carModification[CAR_SPEED_DIFF_IDX].get<float>();
        auto healingPoints = carModification[CAR_HEALING_POINTS_IDX].get<int>();
        auto damagePoints = carModification[CAR_DAMAGE_POINTS_IDX].get<int>();

        car->updateMaxForwardSpeed(forwardSpeedDiff);
        car->receiveHealing(healingPoints);
        car->receiveDamage(damagePoints);
    }
}

PluginRequestsProcessor::~PluginRequestsProcessor() {}
