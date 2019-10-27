#include "ProtectedModel.h"
#include "Entity.h"
#include "Camera.h"
#include "Car.h"
#include <vector>
#include <mutex>
#include "Window.h"
#include "TileMap.h"

ProtectedModel::ProtectedModel(Window& main) :
    main(main) {
    this->entities["a"] = new TileMap(main, "../media/maps/lazy.map");
}

void ProtectedModel::updateEntity(std::string id,
                                  int x,
                                  int y,
                                  int angle,
                                  int health) {
    std::unique_lock<std::mutex> lck(m);
    if  (this->entities.count(id) == 0) {
        this->entities[id] = new Car("../media/sprites/pitstop_car_1.png", 100, 100, main);
    }
    if (this->entities["zzz"] == NULL) {
        this->entities["zzz"] = new Camera(this->main, *this->entities["tomas"]);
    }
    entities[id]->setPos(x, y, angle);
}

void ProtectedModel::renderAll() {
    std::unique_lock<std::mutex> lock(m);
    if (!entities.empty()) {
        std::map<std::string, Entity *>::iterator it;
        for (it = entities.begin(); it != entities.end(); ++it)
            it->second->render();
    }
}

ProtectedModel::~ProtectedModel(){
    std::map<std::string, Entity*>::iterator it;
    for (it = entities.begin(); it != entities.end(); ++it)
        delete it->second;

}
