//
// Created by eliana on 26/10/19.
//

#include "Curve.h"

Curve::Curve(b2Body *body) :
    Entity(CURVE, body),
    body(body) {}

void Curve::collide(Entity *entity) {

}

void Curve::endCollision(Entity *entity) {

}
