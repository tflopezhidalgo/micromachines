#ifndef MICROMACHINES_RACEMANAGER_H
#define MICROMACHINES_RACEMANAGER_H


#include <string>
#include <unordered_map>
#include "Car.h"
#include "Track.h"
#include "Checkpoint.h"
#include "Client.h"
#include "World.h"
#include "StageBuilder.h"
#include "EntitiesManager.h"
#include "TimedEvent.h"
#include "../plugins-management/PluginsManager.h"

class RaceManager {
private:
    std::map<std::string,float> &config;
    std::vector<TimedEvent> timedEvents;
    StageBuilder stageBuilder;
    World world;
    RaceJudge raceJudge;
    EntitiesManager entitiesManager;
    PluginsManager* pluginsManager;
    
    std::unordered_map<std::string, Car*> cars;
    
    std::vector<Grandstand*> grandstands;
    std::vector<Track*> tracks;
    std::vector<Grass*> grassTiles;
    std::vector<Checkpoint*> checkpoints;
    
    std::chrono::time_point<std::chrono::system_clock> start;
    
    void applyPlugins();
    void updateTimedEvents();
    void activateGrandstands();
    void updateCars(std::vector<Event> &events);
    
public:

    RaceManager(std::string& mapName, std::map<std::string,float> &config, int raceLaps);

    void addPlayer(std::string& nickname);

    bool raceFinished();

    void updateModel(std::vector<Event> &events);

    std::string getRaceStatus();

    std::string getRaceData();

    ~RaceManager();
};


#endif //MICROMACHINES_RACEMANAGER_H
