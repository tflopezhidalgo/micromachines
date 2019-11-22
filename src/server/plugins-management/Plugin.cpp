//
// Created by leobellaera on 20/11/19.
//

#include "Plugin.h"

void Plugin::addEntities(nlohmann::json& requests,
        std::vector<std::tuple<EntityIdentifier, float, float>>& entitiesAdditions) {

    nlohmann::json j = nlohmann::json::array();

    for (auto & entityData : entitiesAdditions) {
        EntityIdentifier identifier = std::get<ENTITY_IDENTIFIER_IDX>(entityData);
        float x_pos = std::get<ENTITY_INITIAL_X_POS_IDX>(entityData);
        float y_pos = std::get<ENTITY_INITIAL_Y_POS_IDX>(entityData);
        j.push_back({identifier, x_pos, y_pos});
    }

    requests[ENTITIES_ADDITIONS_KEY] = j;

}

void Plugin::deleteEntities(nlohmann::json& requests,
        std::vector<std::tuple<int>>& entitiesDeletions) {

    nlohmann::json j = nlohmann::json::array();

    for (auto & entityData : entitiesDeletions) {
        int id = std::get<ENTITY_ID_IDX>(entityData);
        j.push_back(id);
    }

    requests[ENTITIES_DELETIONS_KEY] = j;

}

void Plugin::addCarsModifications(nlohmann::json& requests,
        std::vector<std::tuple<std::string, float, int, int>>& carsModificationsData) {
    nlohmann::json j = nlohmann::json::array();

    for (auto & carModificationData : carsModificationsData) {
        std::string carId = std::get<CAR_ID_IDX>(carModificationData);
        float forwardSpeedDiff = std::get<CAR_SPEED_DIFF_IDX>(carModificationData);
        int healingPoints = std::get<CAR_HEALING_POINTS_IDX>(carModificationData);
        int damagePoints = std::get<CAR_DAMAGE_POINTS_IDX>(carModificationData);
        j.push_back({carId, forwardSpeedDiff, healingPoints, damagePoints});
    }

    requests[CARS_MODIFICATIONS_KEY] = j;

}
