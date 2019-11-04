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

class ProtectedModel {
private:
	std::string playerID; 
    std::mutex m;
    std::map<std::string, Car*> entities;
    std::map<std::string, Throwable*> objects;
    Window& main;
    Camera cam;
    TileMap map;


public:
    ProtectedModel(Window& main, std::string playerID);
    void updateCar(std::string& id, int x, int y, int angle, int health);
    void updateObject(std::string& id, std::string& type, int x, int y, bool state);
    void renderAll();
    ~ProtectedModel();
};

#endif
