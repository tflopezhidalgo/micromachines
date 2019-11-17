#include "Receiver.h"
#include "Proxy.h"
#include <nlohmann/json.hpp>
#include "SocketException.h"

Receiver::Receiver(ProtectedModel& model,
                   Proxy& proxy) :
                   model(model),
                   alive(true),
                   proxy(proxy) { }


void Receiver::run() {
    while (alive) {
        try {
            nlohmann::json j = nlohmann::json::parse(proxy.receiveMessage());

            for (auto &car : j["carsData"]) {
                std::string key = car[0].get<std::string>();
                int x = car[1].get<int>();
                int y = car[2].get<int>();
                int angle = car[3].get<int>();
                int health = car[4].get<int>();
                bool onExploding = car[6].get<bool>();
                this->model.updateCar(key, x, y, angle, health, onExploding);
            }

            for (auto &obj : j["entitiesData"]) {
                int key = obj[0].get<int>();
                EntityIdentifier type = obj[1].get<EntityIdentifier>();
                EntityStatus state = obj[2].get<EntityStatus>();
                int x = obj[3].get<int>();
                int y = obj[4].get<int>();
                this->model.updateObject(key, type, x, y, state);
            }
        } catch(std::runtime_error &e){
            this->stop();
        }
    }
}

void Receiver::stop() {
    proxy.stop();
    this->alive = false;
}
