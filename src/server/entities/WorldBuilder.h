//
// Created by leobellaera on 29/10/19.
//

#ifndef MICROMACHINES_WORLDBUILDER_H
#define MICROMACHINES_WORLDBUILDER_H


#include <fstream>
#include <map>
#include <string>
#include "World.h"

class WorldBuilder {
private:
    std::ifstream file;
    std::map<std::string, float>& config;
    nlohmann::json map;
    float height;
    float width;
    void addFloors(World* world, std::vector<Floor*>& floors);
public:
    explicit WorldBuilder(std::string& mapName, std::map<std::string, float>& config);
    World* build(std::vector<Floor*>& tracks);
    ~WorldBuilder();
};


#endif //MICROMACHINES_WORLDBUILDER_H
