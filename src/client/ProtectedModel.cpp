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
initialized(false),
annunciator(w) {
    this->map = NULL;
}

void ProtectedModel::initialize(nlohmann::json data) {
    std::unique_lock<std::mutex> lck(m);

    std::vector<std::string> car_sprites_options;
    car_sprites_options.emplace_back("../media/sprites/pitstop_car_7.png");
    car_sprites_options.emplace_back("../media/sprites/pitstop_car_4.png");
    car_sprites_options.emplace_back("../media/sprites/pitstop_car_10.png");
    car_sprites_options.emplace_back("../media/sprites/pitstop_car_5.png");
    car_sprites_options.emplace_back("../media/sprites/pitstop_car_2.png");
    car_sprites_options.emplace_back("../media/sprites/pitstop_car_9.png");
    car_sprites_options.emplace_back("../media/sprites/pitstop_car_6.png");
    car_sprites_options.emplace_back("../media/sprites/pitstop_car_1.png");
    car_sprites_options.emplace_back("../media/sprites/pitstop_car_11.png");
    car_sprites_options.emplace_back("../media/sprites/pitstop_car_8.png");
    car_sprites_options.emplace_back("../media/sprites/pitstop_car_3.png");

    this->map = new TileMap(this->main, data);

    auto car_it = car_sprites_options.begin();

    for (auto &carData : data["carsData"]) {
        if (car_it == car_sprites_options.end())
            car_it = car_sprites_options.begin();
        this->entities[carData[0]] = new Car(*car_it, main);
        int x = carData[1].get<int>();
        int y = carData[2].get<int>();
        int angle = carData[3].get<int>();
        int health = carData[4].get<int>();
        int lapsDone = carData[5].get<int>();
        bool state = carData[6].get<bool>();

        this->entities[carData[0]]->setState(x * cam.getZoom() / 1000, y * cam.getZoom() / 1000, angle, health,
                                             lapsDone, state);
        std::cout << "LOG - Creando auto" << carData << std::endl;
        ++car_it;
    }

    ObjectFactory factory(main);
    int UP_LIMT = 1000;
    for (auto &grandstandData : data["grandstandsData"]) {
        int x = grandstandData[0].get<int>();
        int y = grandstandData[1].get<int>();
        bool horizontal_enable = grandstandData[2].get<bool>();
        bool vertical_enable = grandstandData[3].get<bool>();
        int angle = 0;
        if (!horizontal_enable && !vertical_enable)       // Traduzo booleanos a angulos
            angle = 3.1415 / 2 * SERIALIZING_RESCAILING;
        else if(!horizontal_enable && vertical_enable)
            angle = - 3.1415 / 2 * SERIALIZING_RESCAILING;
        else if(horizontal_enable && !vertical_enable)
            angle = 3.1415 * SERIALIZING_RESCAILING;
        this->objects[UP_LIMT] = factory.generateObject(GRANDSTAND);
        this->objects[UP_LIMT++]->setPosition(x * cam.getZoom(), y * cam.getZoom(), angle);
    }

    cam.setOnTarget(this->entities[this->playerID]);

    this->initialized = true;
    cv.notify_all();
}

void ProtectedModel::count() {
    std::unique_lock<std::mutex> lck(m);
    while (!initialized)
        cv.wait(lck);
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
    while (!initialized)
        cv.wait(lck);

    entities[id]->setState(x * cam.getZoom() / 1000, y * cam.getZoom() / 1000, angle, health, lapsDone, blinded);
}

void ProtectedModel::updateObject(int id, EntityIdentifier type, int x, int y, EntityStatus state) {
    std::unique_lock<std::mutex> lck(m);
    while (!initialized)
        cv.wait(lck);

    if (objects[id] == NULL) {
        ObjectFactory factory(this->main);
        this->objects[id] = factory.generateObject(type);
    }

    this->objects[id]->setPosition(x * cam.getZoom() / 1000 , y * cam.getZoom() / 1000, 0);
    this->objects[id]->setState(state);
    if (state == DEAD){
        delete this->objects[id];
        objects.erase(id);
    }
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
    for (auto &object : objects)
       object.second->render(cam);
    for (auto& car : entities)
        car.second->render(cam);
    counter.render();
    cam.render();
    annunciator.render();
}

void ProtectedModel::setFinishedGame(std::vector<std::string>& winner) {
    std::unique_lock<std::mutex> lock(m);
    while (!initialized)
        cv.wait(lock);
    this->finished = true;
    cam.setOnTarget(this->entities[winner[0]]);
    this->annunciator.setWinners(winner);
}

std::vector<int> ProtectedModel::getActualState() {
    std::unique_lock<std::mutex> lock(m);
    while (!initialized)
        cv.wait(lock);
    std::vector<int> state;
    state.push_back(this->entities[playerID]->getAngle());
    state.push_back(this->entities[playerID]->getXPos());
    state.push_back(this->entities[playerID]->getYPos());
    return state;
}


std::vector<std::vector<int>> ProtectedModel::getEntitiesPos() {
    std::unique_lock<std::mutex> lock(m);
    while (!initialized)
        cv.wait(lock);
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
    while (!initialized)
        cv.wait(lock);
    return map->getTileNumbers();
}

ProtectedModel::~ProtectedModel(){
    TTF_Quit();
    if (map)
        delete map;
    for (auto& car : entities)
        delete car.second;
    for (auto& object : objects)
        delete object.second;
}

