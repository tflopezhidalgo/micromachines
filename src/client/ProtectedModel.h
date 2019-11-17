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
	std::string playerID; 
    std::mutex m;
    std::map<std::string, Car*> entities;
    std::map<int, Throwable*> objects;
    Window& main;
    Camera& cam;
    TileMap& map;
    Sprite grand_stand;
    Counter counter;

public:
    ProtectedModel(Window& w, nlohmann::json& data, Camera& cam, TileMap& map, std::string& player);
    void count();
    void updateCar(std::string& id, int x, int y, int angle, int health, bool blinded);
    void updateObject(int id, EntityIdentifier type, int x, int y, EntityStatus state);
    void renderAll();
    std::vector<int> getActualState();
    std::vector<std::vector<int>> getEntitiesPos();
    std::vector<std::vector<int>>& getMap();
    ~ProtectedModel();
};

#endif
