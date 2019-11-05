//
// Created by leobellaera on 29/10/19.
//

#include <nlohmann/json.hpp>
#include "FileReadingException.h"
#include "StageBuilder.h"
#include "Macros.h"

#define EXTENSION ".map"
#define PREFIX "../media/maps/"

#define OPENING_ERROR_MSG "An error occurred while\
 trying to open the config file.\n"

StageBuilder::StageBuilder(std::string &mapName, std::map<std::string, float>& config) :
    config(config) {
    std::string mapPath(mapName);
    mapPath = PREFIX + mapPath + EXTENSION;
    file.open(mapPath);
    if (!file.is_open()) {
        throw FileReadingException(OPENING_ERROR_MSG);
    }

    map = nlohmann::json::parse(file);
    height = map["height"].get<float>();
    width = map["width"].get<float>();
}

//builds physical word and adds tracks references in tracks vector.
World* StageBuilder::buildWorld() {
    auto world = new World(height, width, config);
    return world;
}

void StageBuilder::addRaceSurface(World* world, std::vector<Floor*>& floors, RaceJudge& raceJudge) {

    int idx = 0;
    std::vector<int> checkpointsOrder = map["checkpointsOrder"].get<std::vector<int>>();

    float i = float(TILE_SIZE) / 2.f, j = float(TILE_SIZE) / 2.f;
    float w = -width/2.f, h = -height/2.f;

    float grassFriction = config.find(GRASS_FRICTION_KEY)->second;
    float trackFriction = config.find(TRACK_FRICTION_KEY)->second;

    for (auto & row : map["tiles"]) {

        std::vector<int> tilesRow = row.get<std::vector<int>>();

        for (int & tile : tilesRow) {

            switch(tile) {
                case GRASS_ID : {
                    floors.push_back(world->addFloor(w + i, h + j, grassFriction));
                }
                case HORIZONTAL_TRACK_ID: {
                    floors.push_back(world->addFloor(w + i, h + j, trackFriction));
                }
                case VERTICAL_TRACK_ID: {
                    floors.push_back(world->addFloor(w + i, h + j, trackFriction));
                }
                case HORIZONTAL_TRACK_CP_ID: {
                    floors.push_back(world->addFloor(w + i, h + j, trackFriction));
                    world->addCheckpoint(w + i, h + j,false,
                            checkpointsOrder[idx], raceJudge);
                    idx++;
                }
                case VERTICAL_TRACK_CP_ID: {
                    floors.push_back(world->addFloor(w + i, h + j, trackFriction));
                    world->addCheckpoint(w + i, h + j, true,
                            checkpointsOrder[idx], raceJudge);
                    idx++;
                }
                case FIRST_QUAD_CURVE_TRACK_ID: {
                    floors.push_back(world->addFloor(w + i, h + j, trackFriction));
                }
                case SECOND_QUAD_CURVE_TRACK_ID: {
                    floors.push_back(world->addFloor(w + i, h + j, trackFriction));
                }
                case THIRD_QUAD_CURVE_TRACK_ID: {
                    floors.push_back(world->addFloor(w + i, h + j, trackFriction));
                }
                case FOURTH_QUAD_CURVE_TRACK_ID: {
                    floors.push_back(world->addFloor(w + i, h + j, trackFriction));
                }
            }
            i += TILE_SIZE;
        }
        i = TILE_SIZE / 2.f;
        j += TILE_SIZE;
    }
}

//todo std::vector<b2Vec2> getStartingPositions()

StageBuilder::~StageBuilder() {}
