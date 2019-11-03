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
World* WorldBuilder::build(std::vector<Track*>& tracks) {
    auto world = new World(height, width, config);
    addTracks(world, tracks);

    return world;
}

void WorldBuilder::addTracks(World* world, std::vector<Track*>& tracks) {
    float i = float(TRACK_SIZE)/2.f, j = float(TRACK_SIZE)/2.f;
    float w = -width/2.f, h = -height/2.f;

    Track* track;

    for (auto & row : map["tiles"]) {

        std::vector<int> tilesRow = row.get<std::vector<int>>();

        for (int & tile : tilesRow) {

            switch(tile) {
                //todo: done to accept curved tracks
                case HORIZONTAL_TRACK_ID: {
                    track = world->addTrack(w + i, h + j);
                    tracks.push_back(track);
                }
                case VERTICAL_TRACK_ID: {
                    track = world->addTrack(w + i, h + j);
                    tracks.push_back(track);
                }
                case FIRST_QUAD_CURVE_TRACK_ID: {
                    track = world->addTrack(w + i, h + j);
                    tracks.push_back(track);
                }
                case SECOND_QUAD_CURVE_TRACK_ID: {
                    track = world->addTrack(w + i, h + j);
                    tracks.push_back(track);
                }
                case THIRD_QUAD_CURVE_TRACK_ID: {
                    track = world->addTrack(w + i, h + j);
                    tracks.push_back(track);
                }
                case FOURTH_QUAD_CURVE_TRACK_ID: {
                    track = world->addTrack(w + i, h + j);
                    tracks.push_back(track);
                }
                default: ; //do nothing
            }
            i += TRACK_SIZE;
        }
        i = TRACK_SIZE/2.f;
        j += TRACK_SIZE;
    }
}

WorldBuilder::~WorldBuilder() {}
