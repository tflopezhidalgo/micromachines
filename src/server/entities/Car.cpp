//
// Created by leobellaera on 18/10/19.
//

#include <iostream>
#include "Car.h"
#include "Floor.h"
#include "Oil.h"
#include "HealthBooster.h"
#include "Stone.h"
#include "Constants.h"
#include "Checkpoint.h"

#define DEGTORAD 0.017453292f

Car::Car(std::string id, b2Body* body,
        std::vector<Tire*> tires, int carCollisionDamage,
        b2RevoluteJoint* flJoint, b2RevoluteJoint* frJoint) :

        Entity(EntityIdentifier::CAR, body),
        id(id),
        health(100),
        tires(std::move(tires)),
        carCollisionDamage(carCollisionDamage),
        frontLeftJoint(flJoint),
        frontRightJoint(frJoint) {

}

void Car::updateFriction() {
    for (size_t i = 0; i < tires.size(); i++) {
        tires[i]->updateFriction();
    }
}

void Car::updateMove(std::vector<char>& actions) {
    //todo if status DEAD ...

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
        auto floor = dynamic_cast<Floor*>(entity);
        floor->setCarFriction(this);

    } else if (entity->getIdentifier() == CHECKPOINT) {
        auto checkpoint = dynamic_cast<Checkpoint*>(entity);
        checkpoint->activate(this);
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

std::string& Car::getId() {
    return id;
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
