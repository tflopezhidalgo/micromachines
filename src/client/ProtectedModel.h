#ifndef MICROMACHINES_PROTECTEDMODEL_H
#define MICROMACHINES_PROTECTEDMODEL_H

#include <mutex>
#include <map>
#include <string>
#include "Entity.h"
#include "Window.h"
#include "Camera.h"
#include "TileMap.h"
#include "Car.h"
#include "Throwable.h"
#include "Identifiers.h"
#include "Counter.h"

class ProtectedModel {
private:
    bool initialized;
	std::string playerID; 
    std::mutex m;
    std::map<std::string, Car*> entities;
    std::map<int, Throwable*> objects;
    Window& main;
    Camera& cam;
    TileMap* map;
    Texture waiting_players_screen;
    Sprite grand_stand;
    Counter counter;
    bool finished;
    std::vector<std::string> podium;
    Mix_Music* ambience;

public:
    ProtectedModel(Window& w, Camera& cam, std::string& player);
    void initialize(nlohmann::json data);
    void count();
    void updateCar(std::string& id, int x, int y, int angle, int health, int lapsDone, bool blinded);
    void updateObject(int id, EntityIdentifier type, int x, int y, EntityStatus state);
    void renderAll();
    void setFinishedGame(std::vector<std::string>& podium);
    std::vector<int> getActualState();
    std::vector<std::vector<int>> getEntitiesPos();
    std::vector<std::vector<int>>& getMap();
    ~ProtectedModel();
};

#endif
