//
// Created by leobellaera on 29/10/19.
//

#ifndef MICROMACHINES_WORLDBUILDER_H
#define MICROMACHINES_WORLDBUILDER_H


#include <fstream>
#include "World.h"

class WorldBuilder {
private:
    std::ifstream file;
public:
    WorldBuilder(std::string& mapName);
    //World* build();
    ~WorldBuilder();
};


#endif //MICROMACHINES_WORLDBUILDER_H
