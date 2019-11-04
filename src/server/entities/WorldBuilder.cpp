//
// Created by leobellaera on 29/10/19.
//

#include <nlohmann/json.hpp>
#include "Macros.h"
#include "FileReadingException.h"
#include "WorldBuilder.h"

#define EXTENSION ".map"
#define PREFIX "../media/maps/"

#define OPENING_ERROR_MSG "An error occurred while\
 trying to open the config file.\n"


WorldBuilder::WorldBuilder(std::string &mapName, std::map<std::string, float>& config) :
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
World* WorldBuilder::build(std::vector<Floor*>& tracks) {
    auto world = new World(height, width, config);
    addFloors(world, tracks);

    return world;
}

void WorldBuilder::addFloors(World* world, std::vector<Floor*>& tracks) {
    float i = float(TRACK_SIZE)/2.f, j = float(TRACK_SIZE)/2.f;
    float w = -width/2.f, h = -height/2.f;

    Floor* track;
    
    float grassFriction = config.find(GRASS_FRICTION_KEY)->second;
    float trackFriction = config.find(TRACK_FRICTION_KEY)->second;

    for (auto & row : map["tiles"]) {

        std::vector<int> tilesRow = row.get<std::vector<int>>();

        for (int & tile : tilesRow) {

            switch(tile) {
                
                case GRASS_ID: {
                    track = world->addFloor(w + i, h + j, grassFriction);
                    tracks.push_back(track);
                }
                
                case HORIZONTAL_TRACK_ID: {
                    track = world->addFloor(w + i, h + j, trackFriction);
                    tracks.push_back(track);
                }
                case VERTICAL_TRACK_ID: {
                    track = world->addFloor(w + i, h + j, trackFriction);
                    tracks.push_back(track);
                }
                case FIRST_QUAD_CURVE_TRACK_ID: {
                    track = world->addFloor(w + i, h + j, trackFriction);
                    tracks.push_back(track);
                }
                case SECOND_QUAD_CURVE_TRACK_ID: {
                    track = world->addFloor(w + i, h + j, trackFriction);
                    tracks.push_back(track);
                }
                case THIRD_QUAD_CURVE_TRACK_ID: {
                    track = world->addFloor(w + i, h + j, trackFriction);
                    tracks.push_back(track);
                }
                case FOURTH_QUAD_CURVE_TRACK_ID: {
                    track = world->addFloor(w + i, h + j, trackFriction);
                    tracks.push_back(track);
                }
            }
            i += TRACK_SIZE;
        }
        i = TRACK_SIZE/2.f;
        j += TRACK_SIZE;
    }
}

WorldBuilder::~WorldBuilder() {}
