#include "ProtectedModel.h"
#include "Car.h"
#include <vector>
#include <mutex>
#include "Window.h"
#include "ObjectFactory.h"
#include <string>
#include "Identifiers.h"
#include "Constants.h"
#include "Text.h"
#include <SDL2/SDL_ttf.h>

ProtectedModel::ProtectedModel(Window& w, Camera& cam, std::string& playerID) :
cam(cam),
main(w),
playerID(playerID),
waiting_players_screen(std::move(main.createTextureFrom("../media/sprites/waiting_players.png"))),
counter(w),
finished(false),
initialized(false) { }

void ProtectedModel::initialize(nlohmann::json data) {
    std::unique_lock<std::mutex> lck(m);

    this->map = new TileMap(this->main, data);

    for (auto &carData : data["carsData"]) {
        std::cout << "LOG - Creando auto" << carData << std::endl;
        this->entities[carData[0]] = new Car("../media/sprites/pitstop_car_1.png", main);
        int x = carData[1].get<int>();
        int y = carData[2].get<int>();
        int angle = carData[3].get<int>();
        int health = carData[4].get<int>();
        int lapsDone = carData[5].get<int>();
        bool state = carData[6].get<bool>();

        this->entities[carData[0]]->setState(x * cam.getZoom() / 1000, y * cam.getZoom() / 1000, angle, health,
                                             lapsDone, state);
    }

    ObjectFactory factory(main);
    int UP_LIMT = 1000;
    for (auto &grandstandData : data["grandstandsData"]) {
        int x = grandstandData[0].get<int>();
        int y = grandstandData[1].get<int>();
        this->objects[UP_LIMT] = factory.generateObject(GRANDSTAND);
        this->objects[UP_LIMT++]->setPosition(x * cam.getZoom(), y * cam.getZoom());
    }

    cam.setOnTarget(this->entities[this->playerID]);

    this->initialized = true;
}

void ProtectedModel::count() {
    std::unique_lock<std::mutex> lck(m);
    this->counter.count();
}

void ProtectedModel::updateCar(std::string& id,
                                  int x,
                                  int y,
                                  int angle,
                                  int health,
                                  int lapsDone,
                                  bool blinded) {
    std::unique_lock<std::mutex> lck(m);

    entities[id]->setState(x * cam.getZoom() / 1000, y * cam.getZoom() / 1000, angle, health, lapsDone, blinded);
}

void ProtectedModel::updateObject(int id, EntityIdentifier type, int x, int y, EntityStatus state) {
    std::unique_lock<std::mutex> lck(m);

    if (objects[id] == NULL) {
        ObjectFactory factory(this->main);
        this->objects[id] = factory.generateObject(type);
    }

    this->objects[id]->setPosition(x * cam.getZoom() / 1000 , y * cam.getZoom() / 1000);
    this->objects[id]->setState(state);
}

void ProtectedModel::renderAll() {
    std::unique_lock<std::mutex> lock(m);
    if (!initialized) {
        SDL_Rect r = {0, 0, main.getWidth(), main.getHeight()};
        this->waiting_players_screen.render(r, 0);
        return;
    }
    map->render(cam);
    cam.update();
    for (auto& object : objects)
        object.second->render(cam);
    for (auto& car : entities)
        car.second->render(cam);
    counter.render(0, 0);
    cam.render();
    if (this->finished) {
        int h = -650;
        Text text(this->main, "../media/fonts/myFont.TTF", 60);
        SDL_Rect r = {(main.getWidth() - 650) / 2, (main.getHeight() + h) / 2, 650, 200};
        std::string msg = "CARRERA FINALIZADA";
        text.setText(msg);
        text.render(r);
        SDL_Color color = {255, 0, 0};
        text.setColor(color);
        for (std::string& car : podium) {
            text.setText(car);
            h += 350;
            SDL_Rect r = {(main.getWidth() - 400) / 2, (main.getHeight() + h) / 2, 400, 150};
            text.render(r);
        }
    }
}

void ProtectedModel::setFinishedGame(std::vector<std::string>& winner) {
    std::unique_lock<std::mutex> lock(m);
    this->finished = true;
    this->podium = std::move(winner);
}

bool ProtectedModel::isInitialized() {
    std::unique_lock<std::mutex> lck(this->m);
    return this->initialized;
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
    std::unique_lock<std::mutex> lock(m);
    return map->getTileNumbers();
}

ProtectedModel::~ProtectedModel(){
    TTF_Quit();
    delete map;
    for (auto& car : entities)
        delete car.second;
    for (auto& object : objects)
        delete object.second;
}
