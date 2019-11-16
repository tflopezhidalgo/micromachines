#ifndef MICROMACHINES_GRASS_H
#define MICROMACHINES_GRASS_H


#include "Entity.h"
#include "Car.h"

class Grass : public Entity {
private:
    float friction;
public:
    Grass(b2Body* body, float friction);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void setCarFriction(Car* car);
    void updateCarSurface(Car* car);
    ~Grass();
};

#endif //MICROMACHINES_GRASS_H
