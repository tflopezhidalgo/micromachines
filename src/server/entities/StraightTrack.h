//
// Created by leobellaera on 31/10/19.
//

#ifndef MICROMACHINES_STRAIGHTTRACK_H
#define MICROMACHINES_STRAIGHTTRACK_H



#include "Box2D/Box2D.h"
#include "Entity.h"

class StraightTrack : public Entity {
private:
public:
    StraightTrack(b2Body* body);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    ~StraightTrack();
};


#endif //MICROMACHINES_STRAIGHTTRACK_H
