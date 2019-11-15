//
// Created by eliana on 20/10/19.
//

#ifndef TESTING_STONE_H
#define TESTING_STONE_H

#include "Entity.h"
#include "Car.h"

class Stone : public Entity {
private:
    int damage;
public:
    Stone(b2Body* body, int damage);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void damageCar(Car* car);
    ~Stone();
};


#endif //TESTING_STONE_H
