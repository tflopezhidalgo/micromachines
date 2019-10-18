//
// Created by leobellaera on 18/10/19.
//

#include "Car.h"

#define DENSITY 1
#define HEIGHT 3.f
#define WIDTH 1.5f

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

Car::Car(b2World* world) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {50.f, 50.f}; //HARCODEADO! SE RECIBE X CONSTRUCTOR
    body = world->CreateBody(&bodyDef);

    b2PolygonShape polygon;
    polygon.SetAsBox(WIDTH/2, HEIGHT/2);
    body->CreateFixture(&polygon, DENSITY);

    body->SetUserData(this);

    maxForwardSpeed = 100.f;
    maxBackwardSpeed = -20.f;
    maxDriveForce = 150.f;
}

void Car::updateFriction() {
    b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    body->ApplyAngularImpulse( 0.1f * body->GetInertia() * -body->GetAngularVelocity(), true);
    /*b2Vec2 currentForwardNormal = getForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -2 * currentForwardSpeed;
    body->ApplyForce( dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true)*/;
}

b2Vec2 Car::getLateralVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector( b2Vec2(1,0) );
    return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 Car::getForwardVelocity() {
    b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    return b2Dot(currentForwardNormal, body->GetLinearVelocity()) * currentForwardNormal;
}

void Car::updateDrive(int key) {
    float desiredSpeed = 0;
    switch (key) {
        case UP: desiredSpeed = maxForwardSpeed;  break;
        case DOWN: desiredSpeed = maxBackwardSpeed; break;
        default: return;
    }

    b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

    //apply necessary force
    float force = 0;
    if (desiredSpeed > currentSpeed)
        force = maxDriveForce;
    else if (desiredSpeed < currentSpeed)
        force = -maxDriveForce;
    else
        return;
    updateFriction(); //dont know if its ok
    body->ApplyForce( force * currentForwardNormal, body->GetWorldCenter(), true);
}

void Car::updateTurn(int key) {
    if (body->GetLinearVelocity().Length() == 0) {
        return;
    }
    float desiredTorque = 0;
    switch (key) {
        case LEFT:  desiredTorque = -15;  break;
        case RIGHT: desiredTorque = 15; break;
        default: return;
    }
    updateFriction(); //dont know if its ok
    body->ApplyTorque(desiredTorque, true);
}

b2Vec2 Car::getPosition() {
    return body->GetPosition();
}

float Car::getAngle() {
    return body->GetAngle();
}

Car::~Car() {
    body->GetWorld()->DestroyBody(body);
}
