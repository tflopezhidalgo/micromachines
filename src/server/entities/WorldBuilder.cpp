//
// Created by leobellaera on 29/10/19.
//

#include <nlohmann/json.hpp>
#include "FileReadingException.h"
#include "WorldBuilder.h"

#define EXTENSION ".json"
#define PREFIX "../media/maps/"

#define OPENING_ERROR_MSG "An error occurred while\
 trying to open the config file.\n"


WorldBuilder::WorldBuilder(std::string &mapName) {
    std::string mapPath(mapName);
    mapPath = PREFIX + mapPath + EXTENSION;
    file.open(mapPath);
    if (!file.is_open()) {
        throw FileReadingException(OPENING_ERROR_MSG);
    }
}

//todo
World* WorldBuilder::build() {
   /*nlohmann::json map = nlohmann::json::parse(file);
   for (auto & row : map["tiles"]) {
       std::vector<int> tilesRow = row.get<std::vector<int>>();
       for (int & tile : tilesRow) {
           switch(tile) {
               case 1 :

           }
       }
   }*/
}

WorldBuilder::~WorldBuilder() {}
