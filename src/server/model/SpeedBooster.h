//
// Created by eliana on 26/10/19.
//

#ifndef TESTING_SPEEDBOOSTER_H
#define TESTING_SPEEDBOOSTER_H

#include "Car.h"
#include "Entity.h"
#include <map>

class SpeedBooster : public Entity {
private:
    float defaultMaxForwardSpeed;
    float speedBoost;
public:
    SpeedBooster(b2Body *body,
            float speedBoost,
            float defaultMaxForwardSpeed);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    ~SpeedBooster();
};


#endif //TESTING_SPEEDBOOSTER_H
