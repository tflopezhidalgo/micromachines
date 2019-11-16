//
// Created by leobellaera on 29/10/19.
//

#include <nlohmann/json.hpp>
#include "FileReadingException.h"
#include "StageBuilder.h"
#include "Constants.h"

#define EXTENSION ".map"
#define PREFIX "../media/maps/"

#define OPENING_ERROR_MSG "An error occurred while\
 trying to open the map data file.\n"

StageBuilder::StageBuilder(std::string &mapName, std::map<std::string, float>& config) :
    config(config),
    startingPosIndex(0) {
    std::string mapPath(mapName);
    mapPath = PREFIX + mapPath + EXTENSION;
    file.open(mapPath);
    if (!file.is_open()) {
        throw FileReadingException(OPENING_ERROR_MSG);
    }

    map = nlohmann::json::parse(file);
    height = map["height"].get<float>();
    width = map["width"].get<float>();
    startingPositions = map["carsStartingPositions"].get<std::vector<std::vector<float>>>();
}

World StageBuilder::buildWorld(std::vector<TimedEvent>& timedEvents) {
    World world(height, width, config, timedEvents);
    return std::move(world);
}

void StageBuilder::addRaceSurface(World& world, std::vector<Track*>& tracks,
                                  std::vector<Grass*> &grassTiles, std::vector<Checkpoint*>& checkpoints,
                                  RaceJudge& raceJudge) {

    int idx = 0;
    std::vector<int> checkpointsOrder = map["checkpointsOrder"].get<std::vector<int>>();

    float i = float(TILE_WIDTH) / 2.f, j = float(TILE_HEIGHT) / 2.f;
    float w = -width/2.f, h = -height/2.f;

    float grassFriction = config.find(GRASS_FRICTION_KEY)->second;
    float trackFriction = config.find(TRACK_FRICTION_KEY)->second;

    for (auto & row : map["tiles"]) {

        std::vector<int> tilesRow = row.get<std::vector<int>>();

        for (int & floorId : tilesRow) {

            if (floorId == GRASS_TILE) {

                grassTiles.push_back(world.addGrass(w + i, h + j, grassFriction));

            } else if (floorId == LEFT_TRACK || floorId == RIGHT_TRACK ||
                floorId == UP_TRACK || floorId == DOWN_TRACK ||
                floorId == THIRD_QUAD_TRACK || floorId == SECOND_QUAD_TRACK ||
                floorId == FIRST_QUAD_TRACK || floorId == FOURTH_QUAD_TRACK) {

                tracks.push_back(world.addTrack(w + i, h + j, floorId, trackFriction));

            } else if (floorId == LEFT_CHECKPOINTED_TRACK || floorId == RIGHT_CHECKPOINTED_TRACK) {

                tracks.push_back(world.addTrack(w + i, h + j, floorId, trackFriction));
                checkpoints.push_back(world.addCheckpoint(w + i,h + j,
                        false, checkpointsOrder[idx], raceJudge));
                idx++;

            } else if (floorId == UP_CHECKPOINTED_TRACK || floorId == DOWN_CHECKPOINTED_TRACK) {

                tracks.push_back(world.addTrack(w + i, h + j, floorId, trackFriction));
                checkpoints.push_back(world.addCheckpoint(w + i, h + j,
                        true, checkpointsOrder[idx], raceJudge));
                idx++;
            }

            i += TILE_WIDTH;

        }
        i = TILE_WIDTH / 2.f;
        j += TILE_HEIGHT;
    }
}

void StageBuilder::addGrandstands(World& world, std::vector<Grandstand*>& grandstands) {
    for (auto& grandstandData : map["grandstandsData"]) {
        float x_pos = grandstandData[0].get<float>();
        float y_pos = grandstandData[1].get<float>();
        bool horizontalDisposal = grandstandData[2].get<bool>();
        bool positiveOrientation = grandstandData[3].get<bool>();

        b2Body* body = world.getGrandstandBody(x_pos, y_pos, horizontalDisposal);
        Grandstand* grandstand = new Grandstand(body,
                config.find(GRANDSTAND_OBJECTS_THROWN)->second,
                x_pos, y_pos, horizontalDisposal, positiveOrientation);
        grandstands.push_back(grandstand);
    }
}

//returns a starting position available for a car.
std::vector<float>& StageBuilder::getStartingPosition() {
    startingPosIndex++;
    return startingPositions[startingPosIndex - 1];
}

std::string StageBuilder::getMapData() {
    return std::move(map.dump());
}

StageBuilder::~StageBuilder() {}
