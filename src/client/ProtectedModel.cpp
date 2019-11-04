#include "ProtectedModel.h"
#include "Entity.h"
#include "Camera.h"
#include "Car.h"
#include <vector>
#include <mutex>
#include "Window.h"
#include "TileMap.h"
#include "ThrowableFactory.h"
#include <string>

ProtectedModel::ProtectedModel(Window& main, std::string playerID) :
    playerID(playerID), 
	main(main), 
	cam(main), 
	map(main, "../media/maps/simple.json",  cam.getZoom(), 100) {}

void ProtectedModel::updateCar(std::string& id,
                                  int x,
                                  int y,
                                  int angle,
                                  int health) {
    std::unique_lock<std::mutex> lck(m);

    if (entities.count(id) == 0)
        this->entities[id] = new Car("../media/sprites/pitstop_car_1.png", main);

    if (!cam.targetSet()) 
        cam.setOnTarget(this->entities[this->playerID]);

    entities[id]->setPos(x * cam.getZoom() / 1000, y * cam.getZoom() / 1000, angle);
}

void ProtectedModel::updateObject(std::string &id, std::string &type, int x, int y, bool state) {
    std::unique_lock<std::mutex> lck(m);

    if (objects.count(id) == 0) {
        std::cout << "Se crea objeto id: " << id << std::endl;
        ThrowableFactory factory(this->main);
        this->objects[id] = factory.generateThrowable(type);
    }

    this->objects[id]->setPos(x * cam.getZoom() , y * cam.getZoom());
    this->objects[id]->setState(state);
}

void ProtectedModel::renderAll() {
    std::unique_lock<std::mutex> lock(m);
    if (this->cam.targetSet()) {
        map.render(cam);
        cam.update();
        for (auto& object : objects)
            object.second->render(cam);
        for (auto& car : entities)
            car.second->render(cam);
    }
}

ProtectedModel::~ProtectedModel(){
    std::map<std::string, Entity*>::iterator it;
    for (auto& car : entities)
        delete car.second;
    for (auto& object : objects)
        delete object.second;
}
