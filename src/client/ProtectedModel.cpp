#include "ProtectedModel.h"
#include "Entity.h"
#include "Car.h"
#include <vector>
#include <mutex>
#include "Window.h"

ProtectedModel::ProtectedModel(Window& main) :
    main(main) { }

void ProtectedModel::updateEntity(std::string id,
                                  int x,
                                  int y,
                                  int health) {
    std::unique_lock<std::mutex> lck(m);
    if  (this->entities.count(id) == 0) {
        this->entities[id] = new Car("../media/sprites/pitstop_car_1.png", 100, 100, main);
        std::cout << "Se agrega nuevo entity " << entities[id] << "\n";
        std::cout << "Tamaño del mapa " << entities.size() << std::endl;
    }

    entities[id]->setPos(x, y);
}

void ProtectedModel::renderAll() {
    std::unique_lock<std::mutex> lock(m);
    std::map<std::string, Entity*>::iterator it;
    for (it = entities.begin(); it != entities.end(); ++it)
        it->second->render();
}

ProtectedModel::~ProtectedModel(){
    std::map<std::string, Entity*>::iterator it;
    for (it = entities.begin(); it != entities.end(); ++it)
        delete it->second;

}
