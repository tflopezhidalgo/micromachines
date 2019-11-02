#include "ProtectedModel.h"
#include "Entity.h"
#include "Camera.h"
#include "Car.h"
#include <vector>
#include <mutex>
#include "Window.h"
#include "TileMap.h"
#include <string>

ProtectedModel::ProtectedModel(Window& main, std::string playerID) :
    playerID(playerID), 
	main(main), 
	cam(main), 
	map(main, "../media/maps/lazy.map",  cam.getZoom(), 100) {}

void ProtectedModel::updateEntity(std::string id,
                                  int x,
                                  int y,
                                  int angle,
                                  int health) {
    std::unique_lock<std::mutex> lck(m);
    if  (this->entities[id] == NULL)
        this->entities[id] = new Car("../media/sprites/pitstop_car_1.png", main);

    if (!cam.targetSet()) 
        cam.setOnTarget(this->entities[this->playerID]);

    entities[id]->setPos(x * cam.getZoom(), y * cam.getZoom(), angle);
}

void ProtectedModel::renderAll() {
    std::unique_lock<std::mutex> lock(m);
    if (this->cam.targetSet()) {
        map.render(cam);
        cam.update();
        std::map<std::string, Entity*>::iterator it;
        for (it = entities.begin(); it != entities.end(); ++it)
            it->second->render(cam);
    }
}

ProtectedModel::~ProtectedModel(){
    std::map<std::string, Entity*>::iterator it;
    for (it = entities.begin(); it != entities.end(); ++it)
        delete it->second;

}
