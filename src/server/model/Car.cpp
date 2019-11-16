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
#include "SpeedBooster.h"

#define DEGTORAD 0.017453292f

Car::Car(std::string id, std::vector<TimedEvent>& timedEvents, b2Body* body,
        b2Vec2 startingPosition, std::vector<Tire*> tires, int carCollisionDamage,
        b2RevoluteJoint* flJoint, b2RevoluteJoint* frJoint) :

        Entity(EntityIdentifier::CAR, body),
        id(id),
        timedEvents(timedEvents),
        tires(std::move(tires)),
        carCollisionDamage(carCollisionDamage),
        frontLeftJoint(flJoint),
        frontRightJoint(frJoint),
        actualSurface(TRACK),
        lastPosOnTrack(startingPosition),
        respawnPosition(startingPosition),
        respawnAngle(0),
        reducedVision(false) {}

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
        updatePosition();
        receiveDamage(100);
        timedEvents.emplace_back(TimedEvent(this, &Car::recoverHealth, 3));
        return;
    }
    
    for (auto & tire : tires) {
        tire->updateDrive(actions);
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

void Car::recoverHealth() {
    health.receiveHealing(100);
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
        auto stone = dynamic_cast<Stone *>(entity);
        stone->damageCar(this);
        timedEvents.emplace_back(TimedEvent(this, &Car::resetMaxForwardSpeed, 10));
        stone->die();

    } else if (identifier == SPEEDBOOSTER) {
        auto speedBooster = dynamic_cast<SpeedBooster*>(entity);
        speedBooster->boostMaxSpeed(this);
        timedEvents.emplace_back(TimedEvent(this, &Car::resetMaxForwardSpeed, 10));
        speedBooster->die();

    } else if (identifier == OIL) {
        auto oil = dynamic_cast<Oil*>(entity);
        //todo
        oil->die();

    } else if (identifier == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        car->receiveDamage(carCollisionDamage);
        this->receiveDamage(carCollisionDamage);

        if (car->isDead()) {
            car->updatePosition();
            timedEvents.emplace_back(TimedEvent(car, &Car::recoverHealth, 3));
        }
        if (this->isDead()) {
            updatePosition();
            timedEvents.emplace_back(TimedEvent(this, &Car::recoverHealth, 3));
        }

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

    if (identifier == TRACK) {
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

bool Car::isDead() {
    return health.isDead();
}

bool Car::hasReducedVision() {
    return reducedVision;
}

void Car::updateSurface(int surface) {
    actualSurface = surface;
}

void Car::updatePosition() {
    move(respawnPosition, respawnAngle);
    updateSurface(TRACK);
    for (auto & tire : tires) {
        tire->setTransform(respawnPosition, respawnAngle);
    }
    lastPosOnTrack = getPosition();
}

void Car::updateMaxForwardSpeed(float difference) {
    for (auto tire : tires) {
        tire->updateMaxForwardSpeed(difference);
    }
}

void Car::resetMaxForwardSpeed() {
    for (auto tire : tires) {
        tire->resetMaxForwardSpeed();
    }
}

Car::~Car() {
    for (auto & tire : tires) {
        delete tire;
    }
}
