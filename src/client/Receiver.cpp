#include "Receiver.h"
#include "Proxy.h"
#include <nlohmann/json.hpp>

Receiver::Receiver(ProtectedModel& model,
                   Proxy& proxy) :
    model(model), alive(true), proxy(proxy) { }


void Receiver::run() {
    while (alive) {
        nlohmann::json j = nlohmann::json::parse(proxy.receiveMessage());
        for (auto it = j.begin(); it != j.end(); ++it) {
            for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
                auto it3 = it2->begin();
                std::string key = *it3;
                int x = *(++it3);
                int y = *(++it3);
                int angle = *(++it3);
                this->model.updateEntity(key, x, y, angle, 100);
            }
        }
    }
}

void Receiver::stop() {
    this->alive = false;
}
