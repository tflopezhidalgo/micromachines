//
// Created by leobellaera on 18/10/19.
//

#include "Car.h"

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

Car::Car(b2World* world, float pos_x, float pos_y, CrashType type) :
    type(type),
    health(100),
    is_dead(false) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {pos_x, pos_y}; //HARCODEADO! SE RECIBE X CONSTRUCTOR
    body = world->CreateBody(&bodyDef);
    body->SetAngularDamping(3);

    b2Vec2 vertices[8];
    vertices[0].Set( 1.5,   0);
    vertices[1].Set(   3, 2.5);
    vertices[2].Set( 2.8, 5.5);
    vertices[3].Set(   1,  10);
    vertices[4].Set(  -1,  10);
    vertices[5].Set(-2.8, 5.5);
    vertices[6].Set(  -3, 2.5);
    vertices[7].Set(-1.5,   0);
    b2PolygonShape polygonShape;
    polygonShape.Set(vertices, 8);
    b2Fixture* fixture = body->CreateFixture(&polygonShape, 0.1f);

    //prepare common joint parameters
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = body;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0;
    jointDef.upperAngle = 0;
    jointDef.localAnchorB.SetZero();//center of tire

    float maxForwardSpeed = 250;
    float maxBackwardSpeed = -40;
    float backTireMaxDriveForce = 300;
    float frontTireMaxDriveForce = 500;
    float backTireMaxLateralImpulse = 8.5;
    float frontTireMaxLateralImpulse = 7.5;

    //back left tire
    Tire* tire = new Tire(world);
    tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
    jointDef.bodyB = tire->body;
    jointDef.localAnchorA.Set( -3, 0.75f );
    world->CreateJoint( &jointDef );
    tires.push_back(tire);

    //back right tire
    tire = new Tire(world);
    tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, backTireMaxDriveForce, backTireMaxLateralImpulse);
    jointDef.bodyB = tire->body;
    jointDef.localAnchorA.Set( 3, 0.75f );
    world->CreateJoint( &jointDef );
    tires.push_back(tire);

    //front left tire
    tire = new Tire(world);
    tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
    jointDef.bodyB = tire->body;
    jointDef.localAnchorA.Set( -3, 8.5f );
    flJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
    tires.push_back(tire);

    //front right tire
    tire = new Tire(world);
    tire->setCharacteristics(maxForwardSpeed, maxBackwardSpeed, frontTireMaxDriveForce, frontTireMaxLateralImpulse);
    jointDef.bodyB = tire->body;
    jointDef.localAnchorA.Set( 3, 8.5f );
    frJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
    tires.push_back(tire);

    body->SetUserData((void*)this);
    fixture->SetUserData((void*)this);
}

void Car::getDamage(int damage) {
    health = health - damage;
    if (health <= 0) {
        is_dead = true;
    }
}

bool Car::isDead() {
    return is_dead;
}

CrashType Car::getType() {
    return type;
}

b2Vec2 Car::getPosition() {
    return body->GetPosition();
}

float Car::getAngle() {
    return body->GetAngle();
}

void Car::update(int controlState) {
    for (int i = 0; i < tires.size(); i++)
        tires[i]->updateFriction();
    for (int i = 0; i < tires.size(); i++) {
        tires[i]->updateDrive(controlState);
    }

    float lockAngle = 35 * DEGTORAD;
    float turnSpeedPerSec = 160 * DEGTORAD;
    float turnPerTimeStep = turnSpeedPerSec / 60.0f;
    float desiredAngle = 0;
    switch (controlState) {
        case RIGHT:  desiredAngle = lockAngle;  break;
        case LEFT: desiredAngle = -lockAngle; break;
        default: ;//nothing
    }
    float angleNow = flJoint->GetJointAngle();
    float angleToTurn = desiredAngle - angleNow;
    angleToTurn = b2Clamp( angleToTurn, -turnPerTimeStep, turnPerTimeStep);
    float newAngle = angleNow + angleToTurn;
    flJoint->SetLimits( newAngle, newAngle );
    frJoint->SetLimits( newAngle, newAngle );
}

Car::~Car() {
    body->GetWorld()->DestroyBody(body);
}
