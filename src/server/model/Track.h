#ifndef MICROMACHINES_TRACK_H
#define MICROMACHINES_TRACK_H

#include "Box2D/Box2D.h"
#include "Entity.h"
#include "Car.h"

class Track : public Entity {
private:
    float friction;
    b2Vec2 position;
    float angle;
    int floorId;
public:
    Track(b2Body* body, b2Vec2 position, int floorId, float friction);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void setCarFriction(Car* car);
    void updateCarSurface(Car* car);
    void updateRespawnData(Car* car);
    ~Track();
};

#endif //MICROMACHINES_TRACK_H
