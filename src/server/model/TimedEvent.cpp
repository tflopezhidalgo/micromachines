#include "TimedEvent.h"

TimedEvent::TimedEvent(Car* car, void (Car::*cb)(void), float timeout):
    elapsed(0),
    timeout(timeout),
    car(car),
    cb(cb) {}

TimedEvent::TimedEvent(TimedEvent &&other):
    cb(other.cb) {
    this->car = other.car;
    other.car = nullptr;
    this->elapsed = other.elapsed;
    this->timeout = other.timeout;
}

TimedEvent& TimedEvent::operator=(TimedEvent&& other) {
    if (this == &other) {
        return *this;
    }

    this->car = other.car;
    other.car = nullptr;

    this->timeout = other.timeout;
    other.timeout = 0;

    this->elapsed = other.elapsed;
    other.elapsed = 0;

    this->cb = other.cb;
    other.cb = nullptr;

    return *this;
}

bool TimedEvent::update(float delta) {
    elapsed += delta;
    if (elapsed >= timeout) {
        (car->*cb)();
        return true;
    } else {
        return false;
    }
}

TimedEvent::~TimedEvent() {}