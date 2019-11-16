#ifndef MICROMACHINES_STAGEBUILDER_H
#define MICROMACHINES_STAGEBUILDER_H


#include <fstream>
#include <map>
#include <string>
#include "Checkpoint.h"
#include "Grandstand.h"
#include "Grass.h"
#include "World.h"

class StageBuilder {
private:
    std::ifstream file;
    std::map<std::string, float>& config;
    nlohmann::json map;
    float height;
    float width;
    std::vector<std::vector<float>> startingPositions;
    int startingPosIndex;
public:
    StageBuilder(std::string& mapName, std::map<std::string, float>& config);

    World buildWorld(std::vector<TimedEvent>& timedEvents);

    void addRaceSurface(World& world, std::vector<Track*>& tracks, std::vector<Grass*> &grassTiles,
            std::vector<Checkpoint*>& checkpoints, RaceJudge& raceJudge);

    void addGrandstands(World& world, std::vector<Grandstand*>& grandstands);

    std::vector<float>& getStartingPosition();

    std::string getMapData();

    ~StageBuilder();
};

#endif //MICROMACHINES_STAGEBUILDER_H
