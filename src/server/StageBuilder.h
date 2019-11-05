//
// Created by leobellaera on 29/10/19.
//

#ifndef MICROMACHINES_STAGEBUILDER_H
#define MICROMACHINES_STAGEBUILDER_H


#include <fstream>
#include <map>
#include <string>
#include <entities/Checkpoint.h>
#include "World.h"

class StageBuilder {
private:
    std::ifstream file;
    std::map<std::string, float>& config;
    nlohmann::json map;
    float height;
    float width;
public:
    explicit StageBuilder(std::string& mapName, std::map<std::string, float>& config);
    World* buildWorld();
    void addRaceSurface(World* world, std::vector<Floor*>& floors,
            std::vector<Checkpoint*>& checkpoints, RaceJudge& raceJudge);
    ~StageBuilder();
};

#endif //MICROMACHINES_STAGEBUILDER_H
