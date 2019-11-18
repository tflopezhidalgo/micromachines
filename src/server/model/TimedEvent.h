#ifndef MICROMACHINES_TIMEDEVENT_H
#define MICROMACHINES_TIMEDEVENT_H

#include "Car.h"
#include "Entity.h"

class Car;

class TimedEvent {
private:
    float timeout;
    float elapsed;
    Car* car;
    Entity* entity;
    void (Car::*cbCar)(void);
    void (Entity::*cbEntity)(void);
public:
    TimedEvent(Car* car, void (Car::*cbCar)(void), float timeout);
    TimedEvent(Entity* entity, void (Entity::*cbEntity)(void), float timeout);
    TimedEvent(TimedEvent &&other);
    TimedEvent& operator=(TimedEvent&& other);
    bool update(float delta);
    ~TimedEvent();
};


#endif //MICROMACHINES_TIMEDEVENT_H
