//
// Created by leobellaera on 23/10/19.
//

#include "CarBody.h"

#define DEGTORAD 0.017453292f
#define ANGULAR_DAMPING 3

#define FORWARD 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#include <iostream>

CarBody::CarBody(b2World* world, b2Body* body, std::map<std::string, float>& config) :
    body(body) {
    body->SetAngularDamping(ANGULAR_DAMPING);
    createChassisFixture();

    b2RevoluteJointDef jointDef;
    jointDef.bodyA = body;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0;
    jointDef.upperAngle = 0;
    jointDef.localAnchorB.SetZero();

    //back left tire
    CarTire* tire = new CarTire(world, config);
    joinTireToChassis(world, &jointDef, tire, -3.f, 0.75f);

    //back right tire
    tire = new CarTire(world, config);
    joinTireToChassis(world, &jointDef, tire, 3.f, 0.75f);

    //front left tire
    tire = new CarTire(world, config);
    flJoint = joinTireToChassis(world, &jointDef, tire, -3.f, 13.5f);

    //front right tire
    tire = new CarTire(world, config);
    frJoint = joinTireToChassis(world, &jointDef, tire, 3.f, 13.5f);

}

void CarBody::createChassisFixture() {
    b2Vec2 vertices[4];
    vertices[0].Set(-3,   0);
    vertices[1].Set(3, 0);
    vertices[2].Set(-3, 15);
    vertices[3].Set(3,  15);

    b2PolygonShape polygonShape;
    polygonShape.Set(vertices, 4);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygonShape;
    fixture_def.density = 0.1f;
    fixture_def.isSensor = true;
    fixture_def.shape = &polygonShape;

    body->CreateFixture(&fixture_def);
}

b2RevoluteJoint* CarBody::joinTireToChassis(b2World* world,
                       b2RevoluteJointDef* jointDef,
                       CarTire* tire, float x_pos, float y_pos) {
    jointDef->bodyB = tire->getBody();
    jointDef->localAnchorA.Set(x_pos, y_pos);
    auto joint = (b2RevoluteJoint*)world->CreateJoint(jointDef);
    tires.push_back(tire);
    return joint;

}

void CarBody::move(int action) {
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
    float angleNow = flJoint->GetJointAngle();
    float angleToTurn = desiredAngle - angleNow;
    angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
    float newAngle = angleNow + angleToTurn;
    flJoint->SetLimits(newAngle, newAngle);
    frJoint->SetLimits(newAngle, newAngle);
}


CarBody::~CarBody() {
    for (size_t i = 0; i < tires.size(); ++i) {
        delete tires[i];
    }
}
