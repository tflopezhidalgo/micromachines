#ifndef TESTING_HEALTHBOOSTER_H
#define TESTING_HEALTHBOOSTER_H

#include "Entity.h"
#include "Car.h"

class HealthBooster : public Entity {
private:
    int healthBoost;
    bool used;
    std::vector<TimedEvent>& timedEvents;
public:
    explicit HealthBooster(b2Body* body, int healing, std::vector<TimedEvent>& timedEvents);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void heal(Car* car);
    ~HealthBooster();
};

#endif //TESTING_HEALTHBOOSTER_H
