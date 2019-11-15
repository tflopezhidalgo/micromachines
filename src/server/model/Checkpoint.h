//
// Created by leobellaera on 4/11/19.
//

#ifndef MICROMACHINES_CHECKPOINT_H
#define MICROMACHINES_CHECKPOINT_H


#include <RaceJudge.h>
#include "Entity.h"
#include "Box2D/Box2D.h"
#include "Car.h"

class Checkpoint : public Entity {
private:
    RaceJudge& raceJudge;
    int order;
public:
    Checkpoint(b2Body* body, int checkpointOrder, RaceJudge& raceJudge);
    void activate(Car* car);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    ~Checkpoint();
};

#endif //MICROMACHINES_CHECKPOINT_H
