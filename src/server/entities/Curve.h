//
// Created by eliana on 26/10/19.
//

#ifndef TESTING_CURVE_H
#define TESTING_CURVE_H

#include "Entity.h"
#include "Car.h"

class Curve : public Entity {
private:
    b2Body *body;
public:
    explicit Curve(b2Body *body);
    void collide(Entity *entity) override;
    void endCollision(Entity *entity) override;
};


#endif //TESTING_CURVE_H
