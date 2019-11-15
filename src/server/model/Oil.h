//
// Created by eliana on 20/10/19.
//

#ifndef TESTING_OIL_H
#define TESTING_OIL_H

#include "Entity.h"
#include "Car.h"

class Oil : public Entity {
private:
    float grip;
public:
    Oil(b2Body *body, float grip);
    void beginCollision(Entity* entity) override;
    void endCollision(Entity* entity) override;
    ~Oil();
};


#endif //TESTING_OIL_H
