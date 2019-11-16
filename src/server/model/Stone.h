#ifndef TESTING_STONE_H
#define TESTING_STONE_H

#include "Entity.h"
#include "Car.h"

class Stone : public Entity {
private:
    int damage;
    float speedDecrement;
    std::vector<TimedEvent>& timedEvents;
public:
    Stone(b2Body* body, int damage, float speedDecrement, std::vector<TimedEvent>& timedEvents);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void damageCar(Car* car);
    ~Stone();
};


#endif //TESTING_STONE_H
