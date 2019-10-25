//
// Created by leobellaera on 18/10/19.
//

#include "CarTire.h"

#define FORWARD 1
#define BACKWARD 2
#define LEFT 3
#define RIGHT 4

#define FSPEED_KEY "maxForwardSpeed"
#define BSPEED_KEY "maxBackwardSpeed"
#define DRIVEFORCE_KEY "maxDriveForce"
#define LATIMPULSE_KEY "maxLateralImpulse"

CarTire::CarTire(b2World* world, std::map<std::string, float>& config) :
    maxForwardSpeed(config.find(FSPEED_KEY)->second),
    maxBackwardSpeed(config.find(BSPEED_KEY)->second),
    maxDriveForce(config.find(DRIVEFORCE_KEY)->second),
    maxLateralImpulse(config.find(LATIMPULSE_KEY)->second) {

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    body = world->CreateBody(&bodyDef);
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(0.5f, 1.25f);
    body->CreateFixture(&polygonShape, 1);
}

b2Vec2 CarTire::getLateralVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector( b2Vec2(1,0) );
    return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 CarTire::getForwardVelocity() {
    b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    return b2Dot(currentForwardNormal, body->GetLinearVelocity()) * currentForwardNormal;
}

void CarTire::updateFriction() {
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

void CarTire::updateDrive(int controlState) {
    float desiredSpeed = 0;
    switch (controlState) {
        case FORWARD: desiredSpeed = maxForwardSpeed;  break;
        case BACKWARD: desiredSpeed = maxBackwardSpeed; break;
        default: return;
    }

    b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

    float force = 0;
    if (desiredSpeed > currentSpeed) {
        force = maxDriveForce;
    } else if (desiredSpeed < currentSpeed) {
        force = -maxDriveForce;
    } else {
        return;
    }
    body->ApplyForce(force * currentForwardNormal, body->GetWorldCenter(), true);
}

void CarTire::setCharacteristics(float maxFSpeed, float maxBSpeed,
        float maxDForce, float maxLatImpulse) {
    maxForwardSpeed = maxFSpeed;
    maxBackwardSpeed = maxBSpeed;
    maxDriveForce = maxDForce;
    maxLateralImpulse = maxLatImpulse;
}

b2Body* CarTire::getBody() {
    return body;
}

CarTire::~CarTire() {}
