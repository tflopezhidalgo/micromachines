#include "Receiver.h"
#include "Proxy.h"
#include <nlohmann/json.hpp>
#include "SocketException.h"
#include "Sound.h"
Receiver::Receiver(ProtectedModel& model,
                   Proxy& proxy) :
                   model(model),
                   alive(true),
                   proxy(proxy) { }


void Receiver::run() {

    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);

    Sound count_sound("../media/sounds/count_sound.wav");
    Sound power_up("../media/sounds/power_up_sound.wav");
    Sound crash("../media/sounds/bump_sound.wav");
    Sound brake("../media/sounds/not_accelerating.wav");

    try {
        nlohmann::json j = nlohmann::json::parse(proxy.receiveMessage());

        model.initialize(j);

        std::cout << "LOG - InitialData: " << j.dump() << std::endl;

        proxy.receiveMessage();
        model.count();
        count_sound.play();
        proxy.receiveMessage();
        model.count();
        count_sound.play();
        proxy.receiveMessage();
        model.count();
        count_sound.play();
        proxy.receiveMessage();
        model.count();
        count_sound.play();

        while (alive) {
                nlohmann::json j = nlohmann::json::parse(proxy.receiveMessage());

                for (auto &car : j["carsData"]) {
                    std::string key = car[0].get<std::string>();
                    int x = car[1].get<int>();
                    int y = car[2].get<int>();
                    int angle = car[3].get<int>();
                    int health = car[4].get<int>();
                    int lapsDone = car[5].get<int>();
                    bool onExploding = car[6].get<bool>();
                    int velocity = car[7].get<int>();
                    bool field1 = car[8].get<bool>(); // CHOQUE
                    bool field2 = car[9].get<bool>();
                    this->model.updateCar(key, x, y, angle, health, lapsDone, onExploding);
                    /*if (velocity == 0) {
                        accelerating.stop();
                        brake.play(-1);
                    }
                    if (velocity > 0) {
                        brake.stop();
                        accelerating.play(-1);
                    }*/
                    if (field1)
                        crash.play();
                    if (field2)
                        power_up.play();

                }
                for (auto &obj : j["entitiesData"]) {
                    int key = obj[0].get<int>();
                    EntityIdentifier type = obj[1].get<EntityIdentifier>();
                    EntityStatus state = obj[2].get<EntityStatus>();
                    int x = obj[3].get<int>();
                    int y = obj[4].get<int>();
                    this->model.updateObject(key, type, x, y, state);
                }
                if (j["matchFinished"].get<bool>()) {
                    std::vector<std::string> winners = j["carsArrivalOrder"].get<std::vector<std::string>>();
                    this->model.setFinishedGame(winners);
                }
        }
    } catch(std::runtime_error &e){
        this->stop();
    }
}

void Receiver::stop() {
    proxy.stop();
    this->alive = false;
}

Receiver::~Receiver() {
    this->join();
}
