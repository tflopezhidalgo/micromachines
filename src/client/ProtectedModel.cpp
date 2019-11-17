#include "ProtectedModel.h"
#include "Car.h"
#include <vector>
#include <mutex>
#include "Window.h"
#include "ThrowableFactory.h"
#include <string>
#include "Identifiers.h"

ProtectedModel::ProtectedModel(Window& w, nlohmann::json& data, Camera& cam, TileMap& map, std::string& playerID) :
map(map),
cam(cam),
main(w),
playerID(playerID) {
    std::cout << "Data vale " << data.dump() << std::endl;
    for (auto& carData : data["carsData"]) {
        std::cout << "LOG - Creando auto" << carData << std::endl;
        this->entities[carData[0]] = new Car("../media/sprites/pitstop_car_1.png", w);
        int x = carData[1].get<int>();
        int y = carData[2].get<int>();
        int angle = carData[3].get<int>();
        int health = carData[4].get<int>();
        bool state = carData[6].get<bool>();

        this->entities[carData[0]]->setState(x * cam.getZoom() / 1000, y * cam.getZoom() / 1000, angle, health, state);
    }

    cam.setOnTarget(this->entities[this->playerID]);

}

void ProtectedModel::updateCar(std::string& id,
                                  int x,
                                  int y,
                                  int angle,
                                  int health,
                                  bool onExploding) {
    std::unique_lock<std::mutex> lck(m);

    if (entities[id] != NULL) {
        entities[id]->setState(x * cam.getZoom() / 1000, y * cam.getZoom() / 1000, angle, health, onExploding);
    }
}

void ProtectedModel::updateObject(int id, EntityIdentifier type, int x, int y, EntityStatus state) {
    std::unique_lock<std::mutex> lck(m);

    if (objects[id] == NULL) {
        ThrowableFactory factory(this->main);
        this->objects[id] = factory.generateThrowable(type);
    }

    this->objects[id]->setPos(x * cam.getZoom() / 1000 , y * cam.getZoom() / 1000);
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

std::vector<int> ProtectedModel::getActualState() {
    std::unique_lock<std::mutex> lock(m);
    std::vector<int> state;
    state.push_back(this->entities[playerID]->getAngle());
    state.push_back(this->entities[playerID]->getXPos());
    state.push_back(this->entities[playerID]->getYPos());
    return state;
}


std::vector<std::vector<int>> ProtectedModel::getEntitiesPos() {
    std::unique_lock<std::mutex> lock(m);
    std::vector<std::vector<int>> entities_buf;
    for (auto& object : objects) {
        std::vector<int> entity_buf;
        entity_buf.push_back(object.first);
        entity_buf.push_back(object.second->getXPos());
        entity_buf.push_back(object.second->getYPos());
        entities_buf.push_back(std::move(entity_buf));
    }
    return entities_buf;
}

std::vector<std::vector<int>>& ProtectedModel::getMap() {
    return map.getTileNumbers();
}

ProtectedModel::~ProtectedModel(){
    for (auto& car : entities)
        delete car.second;
    for (auto& object : objects)
        delete object.second;
}
