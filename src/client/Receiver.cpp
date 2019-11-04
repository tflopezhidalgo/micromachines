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
        list.push_back("2");
        list.push_back("HEALTH");
        list.push_back(-20);
        list.push_back(-20);
        list.push_back(true);

        j["objects"].push_back(list);

        nlohmann::json list2;
        list2.push_back("1");
        list2.push_back("BOOST");
        list2.push_back(20);
        list2.push_back(20);
        list2.push_back(true);

        j["objects"].push_back(list2);

        nlohmann::json list3;
        list3.push_back("3");
        list3.push_back("OIL");
        list3.push_back(0);
        list3.push_back(0);
        list3.push_back(true);

        j["objects"].push_back(list3);


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
