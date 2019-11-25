#include <Constants.h>
#include "Track.h"
#include "Car.h"

Track::Track(b2Body* body, b2Vec2 position, int floorId, float friction) :
    Entity(TRACK, body),
    friction(friction),
    position(position),
    floorId(floorId) {

    if (floorId == LEFT_TRACK || floorId == LEFT_WITH_CHECKPOINT_TRACK) {
        angle = 90;

    } else if (floorId == RIGHT_TRACK || floorId == RIGHT_WITH_CHECKPOINT_TRACK) {
        angle = -90;

    } else if (floorId == UP_TRACK || floorId == UP_WITH_CHECKPOINT_TRACK) {
        angle = 180;

    } else if (floorId == DOWN_TRACK || floorId == DOWN_WITH_CHECKPOINT_TRACK ||
        floorId == DOWN_WITH_FLAG_TRACK || floorId == DOWN_WITH_POSITIONS_TRACK) {
        angle = 0;

    } else if (floorId == FIRST_QUAD_TRACK) {
        angle = -45;

    } else if (floorId == SECOND_QUAD_TRACK) {
        angle = -135;

    } else if (floorId == THIRD_QUAD_TRACK) {
        angle = 135;

    } else if (floorId == FOURTH_QUAD_TRACK) {
        angle = 45;
    }
}

void Track::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        setCarFriction(car);
        updateCarSurface(car);
    }
}

void Track::endCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        updateRespawnData(car);
    }
}

void Track::updateRespawnData(Car* car) {
    if (!car) {
        return;
    }

    car->setLastPosOnTrack(car->getPosition());

    if (floorId == FIRST_QUAD_TRACK || floorId == SECOND_QUAD_TRACK ||
    floorId == THIRD_QUAD_TRACK || floorId == FOURTH_QUAD_TRACK) {
        car->setRespawnCoordinates(position, angle);
        return;
    }

    float loX = float(-TILE_WIDTH)/2;
    float hiX =  float(TILE_WIDTH)/2;
    float xPos = loX + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(hiX-loX)));

    float loY = float(-TILE_HEIGHT)/2;
    float hiY =  float(TILE_HEIGHT)/2;
    float yPos = loY + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(hiY-loY)));

    b2Vec2 randPos = {position.x + xPos, position.y + yPos};

    car->setRespawnCoordinates(randPos, angle);
}

void Track::setCarFriction(Car* car) {
    car->setTiresFriction(friction);
}

void Track::updateCarSurface(Car* car) {
    car->updateSurface(TRACK);
}

Track::~Track() {}
