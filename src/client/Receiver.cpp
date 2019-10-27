#include <zconf.h>
#include "Receiver.h"
#include "Proxy.h"
#include "../common/Socket.h"
#include <nlohmann/json.hpp>

Receiver::Receiver(ProtectedModel& model,
                   Proxy& proxy) :
    model(model), alive(true), proxy(proxy) { }


void Receiver::run() {
    std::string msg = proxy.receiveMessage();
    std::cout << msg << std::endl;
    while (alive) {
        nlohmann::json j = nlohmann::json::parse(proxy.receiveMessage());
        int posX = j["x"].get<int>();
        int posY = j["y"].get<int>();
        int angle = j["angle"].get<int>();
        //std::cout << "Se recibe " << j.dump() << std::endl;
        this->model.updateEntity("tomas", posX, posY, angle, 100);
    }
}

void Receiver::stop() {
    this->alive = false;
}