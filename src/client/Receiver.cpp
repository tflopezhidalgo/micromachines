#include <zconf.h>
#include "Receiver.h"
#include "Proxy.h"
#include "../common/Socket.h"
#include <nlohmann/json.hpp>

Receiver::Receiver(ProtectedModel& model,
                   Proxy& proxy) :
    model(model), alive(true), proxy(proxy) { }


void Receiver::run() {
    while (alive) {
        usleep(2);
        nlohmann::json j = nlohmann::json::parse(proxy.receiveMessage());

        for (auto it = j.begin(); it != j.end(); ++it) {
            for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
                auto it3 = it2->begin();
                std::string key = *it3;
                this->model.updateEntity(key, int(*(++it3)), int(*(++it3)), int(*(++it3)), 100);
            }
        }
    }
}

void Receiver::stop() {
    this->alive = false;
}