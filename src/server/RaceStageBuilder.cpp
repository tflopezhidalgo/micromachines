//
// Created by leobellaera on 29/10/19.
//

#include <nlohmann/json.hpp>
#include "FileReadingException.h"
#include "RaceStageBuilder.h"
#include "Constants.h"

#define EXTENSION ".map"
#define PREFIX "../media/maps/"

#define OPENING_ERROR_MSG "An error occurred while\
 trying to open the config file.\n"

RaceStageBuilder::RaceStageBuilder(std::string &mapName, std::map<std::string, float>& config) :
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

//builds physical word and adds tracks references in tracks vector.
World RaceStageBuilder::buildWorld() {
    World world(height, width, config);
    return std::move(world);
}

void RaceStageBuilder::addRaceSurface(World& world, std::vector<Floor*>& floors,
                                      std::vector<Checkpoint*>& checkpoints, RaceJudge& raceJudge) {

    int idx = 0;
    std::vector<int> checkpointsOrder = map["checkpointsOrder"].get<std::vector<int>>();

    float i = float(TILE_WIDTH) / 2.f, j = float(TILE_HEIGHT) / 2.f;
    float w = -width/2.f, h = -height/2.f;

    float grassFriction = config.find(GRASS_FRICTION_KEY)->second;
    float trackFriction = config.find(TRACK_FRICTION_KEY)->second;

    for (auto & row : map["tiles"]) {

        std::vector<int> tilesRow = row.get<std::vector<int>>();

        for (int & tile : tilesRow) {

            if (tile == GRASS_ID) {

                floors.push_back(world.addFloor(w + i, h + j, grassFriction));

            } else if (tile == HORIZONTAL_TRACK_ID || tile == VERTICAL_TRACK_ID ||
            tile == FIRST_QUAD_CURVE_TRACK_ID || tile == SECOND_QUAD_CURVE_TRACK_ID ||
            tile == THIRD_QUAD_CURVE_TRACK_ID || tile == FOURTH_QUAD_CURVE_TRACK_ID) {

                floors.push_back(world.addFloor(w + i, h + j, trackFriction));

            } else if (tile == HOR_TRACK_CHECKPOINT_ID) {

                floors.push_back(world.addFloor(w + i, h + j, trackFriction));
                checkpoints.push_back(world.addCheckpoint(w + i,h + j,
                        false, checkpointsOrder[idx], raceJudge));
                idx++;

            } else if (tile == VER_TRACK_CHECKPOINT_ID) {

                floors.push_back(world.addFloor(w + i, h + j, trackFriction));
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

void RaceStageBuilder::addGrandstands(World& world, std::vector<Grandstand*>& grandstands) {
    for (auto& grandstandData : map["grandstandsData"]) {
        float x_pos = grandstandData[0].get<float>();
        float y_pos = grandstandData[1].get<float>();
        bool horizontalDisposal = grandstandData[2].get<bool>();
        bool positiveOrientation = grandstandData[3].get<bool>();
        b2Body* body = world.getGrandstandBody(x_pos, y_pos, horizontalDisposal);
        Grandstand* grandstand = new Grandstand(body,
                config.find(GRANDSTAND_OBJECTS_THROWN)->second,
                x_pos, y_pos, horizontalDisposal, positiveOrientation);
    }
}

//returns a starting position available for a car.
std::vector<float>& RaceStageBuilder::getStartingPosition() {
    startingPosIndex++;
    return startingPositions[startingPosIndex - 1];
}

RaceStageBuilder::~RaceStageBuilder() {}
