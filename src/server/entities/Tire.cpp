//
// Created by leobellaera on 18/10/19.
//

#include "Tire.h"
#include "Macros.h"

Tire::Tire(b2Body* body, float maxFwSpeed, float maxBwSpeed,
            float maxDriveForce, float maxLatImpulse, float defaultFriction) :
            body(body),
            maxForwardSpeed(maxFwSpeed),
            maxBackwardSpeed(maxBwSpeed),
            maxDriveForce(maxDriveForce),
            maxLateralImpulse(maxLatImpulse),
            actualFriction(defaultFriction) {}

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
    float dragForceMagnitude = -actualFriction * currentForwardSpeed;
    body->ApplyForce(dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true);

    //todo drifting
}

void Tire::updateDrive(std::vector<char>& actions) {

    float desiredSpeed = 0;

    bool moveForward = std::find(actions.begin(), actions.end(), FORWARD) != actions.end();
    bool moveBackward = std::find(actions.begin(), actions.end(), BACKWARD) != actions.end();

    if (moveForward) {
        desiredSpeed = maxForwardSpeed;
    } else if (moveBackward) {
        desiredSpeed = maxBackwardSpeed;
    }

    if ((moveForward && moveBackward) || (!moveForward && !moveBackward)) {
        return;
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

void Tire::setFriction(float newFriction) {
    actualFriction = newFriction;
}

void Tire::setMaxForwardSpeed(float newMaxForwardSpeed) {
    maxForwardSpeed = newMaxForwardSpeed;
}

Tire::~Tire() {
    //todo if tire is a entity in a future, delete this
    body->GetWorld()->DestroyBody(body);
}
