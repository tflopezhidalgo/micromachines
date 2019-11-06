//
// Created by leobellaera on 29/10/19.
//

#ifndef MICROMACHINES_RACESTAGEBUILDER_H
#define MICROMACHINES_RACESTAGEBUILDER_H


#include <fstream>
#include <map>
#include <string>
#include <entities/Checkpoint.h>
#include "World.h"

class RaceStageBuilder {
private:
    std::ifstream file;
    std::map<std::string, float>& config;
    nlohmann::json map;
    float height;
    float width;
    std::vector<std::vector<float>> startingPositions;
    int startingPosIndex;
public:
    explicit RaceStageBuilder(std::string& mapName, std::map<std::string, float>& config);
    World* buildWorld();
    void addRaceSurface(World* world, std::vector<Floor*>& floors,
            std::vector<Checkpoint*>& checkpoints, RaceJudge& raceJudge);
    std::vector<float>& getStartingPosition();
    ~RaceStageBuilder();
};

#endif //MICROMACHINES_RACESTAGEBUILDER_H
