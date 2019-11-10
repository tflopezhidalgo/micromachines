//
// Created by leobellaera on 18/10/19.
//

#include <iostream>
#include "Car.h"
#include "Track.h"
#include "Oil.h"
#include "HealthBooster.h"
#include "Stone.h"
#include "Constants.h"
#include "Checkpoint.h"
#include "Grass.h"

#define DEGTORAD 0.017453292f
#define MAX_DISTANCE_TO_TRACK 200

Car::Car(std::string id, b2Body* body, b2Vec2 startingPosition,
        std::vector<Tire*> tires, int carCollisionDamage,
        b2RevoluteJoint* flJoint, b2RevoluteJoint* frJoint) :

        Entity(EntityIdentifier::CAR, body),
        id(id),
        health(100),
        tires(std::move(tires)),
        carCollisionDamage(carCollisionDamage),
        frontLeftJoint(flJoint),
        frontRightJoint(frJoint),
        actualSurface(TRACK),
        lastPosOnTrack(startingPosition),
        respawnPosition({0,0}),
        respawnAngle(0) {}

void Car::updateFriction() {
    for (size_t i = 0; i < tires.size(); i++) {
        tires[i]->updateFriction();
    }
}

void Car::updateMove(std::vector<char>& actions) {
    if (isDead()) {
        return;
    }

    if (actualSurface == GRASS && (getPosition() - lastPosOnTrack).Length() > MAX_DISTANCE_TO_TRACK) {
        move(respawnPosition, respawnAngle);
        for (auto & tire : tires) {
            tire->setTransform(respawnPosition, respawnAngle);
        }
        return;
    }

    for (size_t i = 0; i < tires.size(); i++) {
        tires[i]->updateDrive(actions);
    }

    float lockAngle = 40 * DEGTORAD;
    float turnSpeedPerSec = 320 * DEGTORAD;
    float turnPerTimeStep = turnSpeedPerSec / 60.0f;

    bool turnRight = std::find(actions.begin(), actions.end(), RIGHT) != actions.end();
    bool turnLeft = std::find(actions.begin(), actions.end(), LEFT) != actions.end();

    float desiredAngle = 0;

    if (turnRight) {
        desiredAngle = lockAngle;
    } else if (turnLeft) {
        desiredAngle = -lockAngle;
    }

    if (turnLeft && turnRight) {
        desiredAngle = 0;
    }

    float angleNow = frontLeftJoint->GetJointAngle();
    float angleToTurn = desiredAngle - angleNow;
    angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
    float newAngle = angleNow + angleToTurn;
    frontLeftJoint->SetLimits(newAngle, newAngle);
    frontRightJoint->SetLimits(newAngle, newAngle);
}

void Car::setTiresFriction(float newFriction) {
    for (auto tire : tires) {
        tire->setFriction(newFriction);
    }
}

void Car::beginCollision(Entity* entity) {

    EntityIdentifier identifier = entity->getIdentifier();

    if (entity->isDead()) {
        return;
    }

    if (identifier == HEALTHBOOSTER) {
        auto healthBooster = dynamic_cast<HealthBooster*>(entity);
        healthBooster->heal(this);
        healthBooster->die();

    } else if (identifier == STONE) {
        auto stone = dynamic_cast<Stone*>(entity);
        stone->damageCar(this);
        stone->die();

    } else if (identifier == OIL) {
        auto oil = dynamic_cast<Oil*>(entity);
        //todo
        oil->die();

    } else if (identifier == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        car->receiveDamage(carCollisionDamage);
        this->receiveDamage(carCollisionDamage);

    } else if (identifier == TRACK) {
        auto track = dynamic_cast<Track*>(entity);
        track->setCarFriction(this);

    } else if (identifier == GRASS) {
        auto grass = dynamic_cast<Grass*>(entity);
        grass->setCarFriction(this);

    } else if (identifier == CHECKPOINT) {
        auto checkpoint = dynamic_cast<Checkpoint*>(entity);
        checkpoint->activate(this);
    }
}

void Car::endCollision(Entity* entity) {

    EntityIdentifier identifier = entity->getIdentifier();

    if (identifier == OIL) {
        //todo
    } else if (identifier == TRACK) {
        auto track = dynamic_cast<Track*>(entity);
        track->updateRespawnData(this);
    }
}

void Car::setLastPosOnTrack(b2Vec2 position) {
    lastPosOnTrack = position;
}

void Car::setRespawnCoordinates(b2Vec2 position, float angle) {
    respawnPosition = position;
    respawnAngle = angle * DEGTORAD;
}

void Car::receiveHealing(int healingPoints) {
    health.receiveHealing(healingPoints);
}

void Car::receiveDamage(int damagePoints) {
    health.receiveDamage(damagePoints);
}

int Car::getHealth() {
    return health.getHealth();
}

std::string& Car::getId() {
    return id;
}

void Car::updateSurface(int surface) {
    actualSurface = surface;
}

void Car::setMaxForwardSpeed(float newMaxForwardSpeed) {
    for (auto tire : tires) {
        tire->setMaxForwardSpeed(newMaxForwardSpeed);
    }
}

Car::~Car() {
    //todo delete joints
    for (auto & tire : tires) {
        delete tire;
    }
}
