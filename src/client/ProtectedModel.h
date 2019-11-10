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

class ProtectedModel {
private:
	std::string playerID; 
    std::mutex m;
    std::map<std::string, Car*> entities;
    std::map<int, Throwable*> objects;
    Window& main;
    Camera cam;
    TileMap map;


public:
    ProtectedModel(Window& main, std::string playerID);
    void updateCar(std::string& id, int x, int y, int angle, int health);
    void updateObject(int id, int type, int x, int y, EntityStatus state);
    void renderAll();
    std::vector<int> getActualState();
    std::vector<std::vector<int>> getEntitiesPos();
    std::vector<std::vector<int>>& getMap();
    ~ProtectedModel();
};

#endif
