//
// Created by leobellaera on 22/11/19.
//

#include "DeleteMudZones.h"

nlohmann::json DeleteMudZones::updateModel(nlohmann::json& model) {
    nlohmann::json requests;

    std::vector<std::tuple<int>> entitiesDeletions;

    for (auto & entityData : model["entitiesData"]) {
        int id = entityData[ENTITY_DATA_ID_IDX].get<int>();
        auto identifier = entityData[ENTITY_DATA_IDENTIFIER_IDX].get<EntityIdentifier>();
        if (identifier == MUD) {
            entitiesDeletions.emplace_back(std::make_tuple(id));
        }
    }

    deleteEntities(requests, entitiesDeletions);
    return std::move(requests);
}

extern "C" Plugin* create() {
    return new DeleteMudZones;
}
