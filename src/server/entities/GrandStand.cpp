//
// Created by leobellaera on 3/11/19.
//

#include "GrandStand.h"

GrandStand::GrandStand(b2Body* body, int objectsThrownNumber, float x_pos, float y_pos) :
    body(body),
    objectsThrownNumber(objectsThrownNumber) {}

void GrandStand::throwObjectsToPilots(std::vector<Entity*> entities) {

}

GrandStand::~GrandStand() {
    body->GetWorld()->DestroyBody(body);
}
