//
// Created by leobellaera on 15/11/19.
//

#ifndef MICROMACHINES_MUD_H
#define MICROMACHINES_MUD_H


#include "Entity.h"
#include "TimedEvent.h"

class Mud : public Entity {
private:
    std::vector<TimedEvent> &timedEvents;
public:
    Mud(b2Body *body, std::vector<TimedEvent> &timedEvents);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void reduceVision(Car* car);
    ~Mud();
};


#endif //MICROMACHINES_MUD_H
