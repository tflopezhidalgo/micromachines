#ifndef MICROMACHINES_TIMEDEVENT_H
#define MICROMACHINES_TIMEDEVENT_H

#include "Car.h"

class Car;

class TimedEvent {
private:
    float timeout;
    float elapsed;
    Car* car;
    void (Car::*cb)(void);
public:
    TimedEvent(Car* car, void (Car::*cb)(void), float timeout);
    TimedEvent(TimedEvent &&other);
    TimedEvent& operator=(TimedEvent&& other);
    bool update(float delta);
    ~TimedEvent();
};


#endif //MICROMACHINES_TIMEDEVENT_H
