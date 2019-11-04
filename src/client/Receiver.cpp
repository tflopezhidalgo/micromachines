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


        nlohmann::json list;
        list.push_back("1");
        list.push_back("ROCK");
        list.push_back(50);
        list.push_back(50);
        list.push_back(true);

        j["objects"].push_back(list);

        std::cout << j.dump() << std::endl;

        for (auto& car : j["carsData"]) {
            std::string key = car[0].get<std::string>();
            int x = car[1].get<int>();
            int y = car[2].get<int>();
            int angle = car[3].get<int>();
            int health = car[4].get<int>();
            this->model.updateCar(key, x, y, angle, health);
        }

        for (auto& obj : j["objects"]) {
            std::string key = obj[0].get<std::string>();
            std::string type = obj[1].get<std::string>();
            int x = obj[2].get<int>();
            int y = obj[3].get<int>();
            bool state = obj[4].get<bool>();
            this->model.updateObject(key, type, x, y, state);
        }

    }
}

void Receiver::stop() {
    this->alive = false;
}
