//
// Created by leobellaera on 18/10/19.
//

#include <iostream>
#include "Car.h"
#include "HealthBooster.h"
#include "Stone.h"
#include "Oil.h"
#include "Track.h"

#define DEGTORAD 0.017453292f
#define LEFT 'L'
#define RIGHT 'R'

Car::Car(b2Body* body, std::vector<Tire*> tires, int carCollisionDamage,
        b2RevoluteJoint* flJoint, b2RevoluteJoint* frJoint) :

        Entity(Identifier::CAR, body),
        health(100),
        tires(std::move(tires)),
        carCollisionDamage(carCollisionDamage),
        frontLeftJoint(flJoint),
        frontRightJoint(frJoint) {}

void Car::update(char action) {
    //if status EXPLODING ...
    for (size_t i = 0; i < tires.size(); i++) {
        tires[i]->updateFriction();
    }
    for (size_t i = 0; i < tires.size(); i++) {
        tires[i]->updateDrive(action);
    }

    float lockAngle = 35 * DEGTORAD;
    float turnSpeedPerSec = 160 * DEGTORAD;
    float turnPerTimeStep = turnSpeedPerSec / 60.0f;
    float desiredAngle = 0;
    switch (action) {
        case RIGHT:  desiredAngle = lockAngle;  break;
        case LEFT: desiredAngle = -lockAngle; break;
        default: ; //nothing to do
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

void Car::resetTiresFriction() {
    for (auto tire : tires) {
        tire->resetFriction();
    }
}

/*void Car::setStatus() {
    status = EXPLODING, etc
}*/

void Car::beginCollision(Entity* entity) {

    if (entity->isDead()) {
        return;
    }

    if (entity->getIdentifier() == HEALTHBOOSTER) {
        auto healthBooster = dynamic_cast<HealthBooster*>(entity);
        healthBooster->heal(this);
        healthBooster->die();
    } else if (entity->getIdentifier() == STONE) {
        auto stone = dynamic_cast<Stone*>(entity);
        stone->damageCar(this);
        stone->die();
    } else if (entity->getIdentifier() == OIL) {
        auto oil = dynamic_cast<Oil*>(entity);
        //todo
        oil->die();
    } else if (entity->getIdentifier() == CAR) {
        auto car = dynamic_cast<Car*>(entity);
        car->receiveDamage(carCollisionDamage);
        this->receiveDamage(carCollisionDamage);
    } else if (entity->getIdentifier() == TRACK) {
        auto track = dynamic_cast<Track*>(entity);
        track->setCarFriction(this);
    }
}

void Car::endCollision(Entity *object) {
    if (object->getIdentifier() == OIL) {
        //todo
    }
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

int Car::getRacePosition() {
    //todo
    return 1;
}

void Car::setMaxForwardSpeed(float newMaxForwardSpeed) {
    for (auto tire : tires) {
        tire->setMaxForwardSpeed(newMaxForwardSpeed);
    }
}

Car::~Car() {
    for (auto & tire : tires) {
        delete tire;
    }
}
