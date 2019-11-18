#include "TimedEvent.h"

TimedEvent::TimedEvent(Car* car, void (Car::*cbCar)(void), float timeout):
    elapsed(0),
    timeout(timeout),
    car(car),
    entity(nullptr),
    cbCar(cbCar),
    cbEntity(nullptr) {}

TimedEvent::TimedEvent(Entity* entity, void (Entity::*cbEntity)(void), float timeout) :
    elapsed(0),
    timeout(timeout),
    car(nullptr),
    entity(entity),
    cbCar(nullptr),
    cbEntity(cbEntity) {}

TimedEvent::TimedEvent(TimedEvent &&other) {
    this->elapsed = other.elapsed;
    this->timeout = other.timeout;

    this->car = other.car;
    other.car = nullptr;
    this->cbCar = other.cbCar;
    other.cbCar = nullptr;

    this->entity = other.entity;
    other.entity = nullptr;
    this->cbEntity = other.cbEntity;
    other.cbEntity = nullptr;
}

TimedEvent& TimedEvent::operator=(TimedEvent&& other) {
    if (this == &other) {
        return *this;
    }

    this->elapsed = other.elapsed;
    this->timeout = other.timeout;

    this->car = other.car;
    other.car = nullptr;
    this->cbCar = other.cbCar;
    other.cbCar = nullptr;

    this->entity = other.entity;
    other.entity = nullptr;
    this->cbEntity = other.cbEntity;
    other.cbEntity = nullptr;

    return *this;
}

bool TimedEvent::update(float delta) {
    elapsed += delta;
    if (elapsed >= timeout) {
        if (car) {
            (car->*cbCar)();
        } else if (entity) {
            (entity->*cbEntity)();
        }
        return true;
    } else {
        return false;
    }
}

TimedEvent::~TimedEvent() {}
