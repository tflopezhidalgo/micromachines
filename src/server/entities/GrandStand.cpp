//
// Created by leobellaera on 3/11/19.
//

#include "GrandStand.h"
#include "Identifiers.h"

//todo Necesitaremos saber la orientacion de la tribuna para tirar los objetos en las posiciones que correspondan.

GrandStand::GrandStand(b2Body* body, int objectsThrownNumber, float x_pos, float y_pos) :
    body(body),
    objectsThrownNumber(objectsThrownNumber) {}

void GrandStand::throwObjectsToPilots(std::vector<Entity*>& entities) {
    int randNumber = rand() % THROWABLE_OBJECTS_NUMBER;
    //b2Vec2 pos = calculateProjectilePosition();

    switch (randNumber) {

        case HEALTHBOOSTER: {

        }

        case OIL : {

        }

        case SPEEDBOOSTER : {

        }

        case MUG : {

        }

        case STONE : {

        }

        default: ; //do nothing
    }

    //return objectsAddedNumber (para el contador)
}

GrandStand::~GrandStand() {
    body->GetWorld()->DestroyBody(body);
}
