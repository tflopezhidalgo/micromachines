#include "ProtectedModel.h"
#include "Entity.h"
#include "Camera.h"
#include "Car.h"
#include <vector>
#include <mutex>
#include "Window.h"
#include "TileMap.h"

ProtectedModel::ProtectedModel(Window& main) :
    main(main), cam(main), map(main, "../media/maps/lazy.map",  1, 100) {}

void ProtectedModel::updateEntity(std::string id,
                                  int x,
                                  int y,
                                  int angle,
                                  int health) {
    std::unique_lock<std::mutex> lck(m);
    if  (this->entities[id] == NULL)
        this->entities[id] = new Car("../media/sprites/pitstop_car_1.png", 100, 100, main);

    if (!cam.targetSet()) {
        cam.setOnTarget(this->entities["tomas"]);
    }

    entities[id]->setPos(x, y, angle);
}

void ProtectedModel::renderAll() {
    std::unique_lock<std::mutex> lock(m);
    map.render(cam);
    cam.update();
    std::map<std::string, Entity *>::iterator it;
        for (it = entities.begin(); it != entities.end(); ++it)
            it->second->render(cam);
}

ProtectedModel::~ProtectedModel(){
    std::map<std::string, Entity*>::iterator it;
    for (it = entities.begin(); it != entities.end(); ++it)
        delete it->second;

}
