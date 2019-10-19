//
// Created by leobellaera on 18/10/19.
//

#include "Tire.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

Tire::Tire(b2World* world) {
b2BodyDef bodyDef;
bodyDef.type = b2_dynamicBody;
body = world->CreateBody(&bodyDef);

b2PolygonShape polygonShape;
polygonShape.SetAsBox( 0.5f, 1.25f );
body->CreateFixture(&polygonShape, 1);

body->SetUserData(this);

}

Tire::~Tire() {
    body->GetWorld()->DestroyBody(body);
}

b2Vec2 Tire::getLateralVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector( b2Vec2(1,0) );
    return b2Dot( currentRightNormal, body->GetLinearVelocity() ) * currentRightNormal;
}

b2Vec2 Tire::getForwardVelocity() {
    b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    return b2Dot( currentForwardNormal, body->GetLinearVelocity() ) * currentForwardNormal;
}

void Tire::updateFriction() {
    //lateral linear velocity
    b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
    if (impulse.Length() > maxLateralImpulse)
        impulse *= maxLateralImpulse / impulse.Length();
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);

    //angular velocity
    body->ApplyAngularImpulse(0.1f * body->GetInertia() * -body->GetAngularVelocity(), true);

    //forward linear velocity
    b2Vec2 currentForwardNormal = getForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -2 * currentForwardSpeed;
    body->ApplyForce(dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true);
}

void Tire::updateDrive(int controlState) {

    //find desired speed
    float desiredSpeed = 0;
    switch (controlState) {
        case UP:   desiredSpeed = maxForwardSpeed;  break;
        case DOWN: desiredSpeed = maxBackwardSpeed; break;
        default: return;//do nothing
    }

    //find current speed in forward direction
    b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot( getForwardVelocity(), currentForwardNormal );

    //apply necessary force
    float force = 0;
    if ( desiredSpeed > currentSpeed )
        force = maxDriveForce;
    else if ( desiredSpeed < currentSpeed )
        force = -maxDriveForce;
    else
        return;
    body->ApplyForce(force * currentForwardNormal, body->GetWorldCenter(), true);
}

void Tire::setCharacteristics(float maxFSpeed, float maxBSpeed, float maxDForce, float maxLatImpulse) {
    maxForwardSpeed = maxFSpeed;
    maxBackwardSpeed = maxBSpeed;
    maxDriveForce = maxDForce;
    maxLateralImpulse = maxLatImpulse;
}

void Tire::updateTurn(int controlState) {
    float desiredTorque = 0;
    switch (controlState) {
        case RIGHT:  desiredTorque = 15;  break;
        case LEFT: desiredTorque = -15; break;
        default: return;
    }
    body->ApplyTorque(desiredTorque, true);
}
