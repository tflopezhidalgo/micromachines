#include "Receiver.h"
#include "Proxy.h"
#include <nlohmann/json.hpp>

Receiver::Receiver(ProtectedModel& model,
                   Proxy& proxy) :
                   model(model),
                   alive(true),
                   proxy(proxy) { }


void Receiver::run() {
    while (alive) {
        nlohmann::json j = nlohmann::json::parse(proxy.receiveMessage());

        for (auto& car : j["carsData"]) {
            std::string key = car[0].get<std::string>();
            int x = car[1].get<int>();
            int y = car[2].get<int>();
            int angle = car[3].get<int>();
            int health = car[4].get<int>();
            this->model.updateCar(key, x, y, angle, health);
        }

        for (auto& obj : j["entitiesData"]) {
            int key = obj[0].get<int>();
            int type = obj[1].get<int>();
            int state = obj[3].get<int>();
            int x = obj[3].get<int>();
            int y = obj[4].get<int>();
            this->model.updateObject(key, type, x, y, state);
        }

    }
}

void Receiver::stop() {
    this->alive = false;
}
