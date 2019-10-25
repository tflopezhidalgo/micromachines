#include "Juego.h"
#include "World.h"

int main() {
    Juego partida({1920, 1080}, "example");
    /*std::map<std::string, float> config;
    config.emplace("maxForwardSpeed", 220.f);
    config.emplace("maxBackwardSpeed", 40.f);
    config.emplace("maxDriveForce", 40.f);
    config.emplace("maxLateralImpulse", 40.f);
    config.emplace("framesPerSecond", 60.f);
    World* world = new World(500, 500, config);
    Car* car = world->addCar(50.f, 50.f);
    car->move(3);
    car->move(3);
    car->move(3);
    car->move(3);
    car->move(3);
    car->move(4);

    world->step();
    car->move(3);
    car->move(3);
    car->move(3);
    car->move(3);
    car->move(2);
    world->step();*/
    return 0;
}
