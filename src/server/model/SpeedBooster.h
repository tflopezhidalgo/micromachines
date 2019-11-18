#ifndef TESTING_SPEEDBOOSTER_H
#define TESTING_SPEEDBOOSTER_H

#include "Car.h"
#include "Entity.h"
#include <map>

class SpeedBooster : public Entity {
private:
    float speedBoost;
    bool used;
    std::vector<TimedEvent>& timedEvents;
public:
    SpeedBooster(b2Body *body, float speedBoost, std::vector<TimedEvent>& timedEvents);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    void boostMaxSpeed(Car* car);
    ~SpeedBooster();
};


#endif //TESTING_SPEEDBOOSTER_H
