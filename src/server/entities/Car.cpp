//
// Created by leobellaera on 18/10/19.
//

#include <iostream>
#include "Car.h"
#include "HealthBooster.h"
#include "Stone.h"
#include "Oil.h"

#define INITIAL_HEALTH 100
#define DEGTORAD 0.017453292f
#define LEFT 'L'
#define RIGHT 'R'

Car::Car(b2Body* body, std::vector<Tire*> tires, b2RevoluteJoint* flJoint, b2RevoluteJoint* frJoint) :
        Entity(Identifier::CAR, body),
        health(INITIAL_HEALTH),
        tires(std::move(tires)),
        frontLeftJoint(flJoint),
        frontRightJoint(frJoint) {}

void Car::move(char action) {
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
        tire->setFrictionFactor(newFriction);
    }
}

/*void Car::setStatus() {
    status = EXPLODING, etc
}*/

void Car::collide(Entity* object) {
    if (object->getIdentifier() == HEALTHBOOSTER) {
        auto healthBooster = dynamic_cast<HealthBooster*>(object);
        healthBooster->boost(this);
    } else if (object->getIdentifier() == STONE) {
        auto stone = dynamic_cast<Stone*>(object);
        //stone->setDead() EL METODO setDead IRA EN LA CLASE ENTITY PARA Q SEA GENERICO
        //if !stone->isDead()
        stone->damageCar(this);
    } else if (object->getIdentifier() == OIL) {
        auto oil = dynamic_cast<Oil*>(object);
        oil->setFriction(this);
    }
}

void Car::collideEnd(Entity *object) {
    if (object->getIdentifier() == OIL) {
        auto oil = dynamic_cast<Oil*>(object);
        oil->resetFriction(this);
    }
}

float Car::getFriction() {
    // eliminar despues
    return tires[0]->getFriction();
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

Car::~Car() {
    for (size_t i = 0; i < tires.size(); i++) {
        delete tires[i];
    }
}
