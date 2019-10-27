//
// Created by eliana on 20/10/19.
//

#ifndef TESTING_STONE_H
#define TESTING_STONE_H

#include "Entity.h"
#include "Car.h"

class Stone : public Entity {
private:
    b2Body* body;
    int damage;
public:
    Stone(b2Body* body);
    void collide(Entity* entity) override;
    void damageCar(Car* car);
};


#endif //TESTING_STONE_H
