#ifndef MICROMACHINES_PROTECTEDMODEL_H
#define MICROMACHINES_PROTECTEDMODEL_H

#include <mutex>
#include <map>
#include <string>
#include "Entity.h"
#include "Window.h"
#include "Camera.h"
#include "TileMap.h"

class ProtectedModel {
private:
	std::string playerID; 
    std::mutex m;
    std::map<std::string, Entity*> entities;
    Window& main;
    Camera cam;
    TileMap map;


public:
    ProtectedModel(Window& main, std::string playerID);
    void updateEntity(std::string, int x, int y, int angle, int health);
    void renderAll();
    ~ProtectedModel();
};

#endif
