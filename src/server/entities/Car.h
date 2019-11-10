//
// Created by leobellaera on 18/10/19.
//

#ifndef TESTING_CAR_H
#define TESTING_CAR_H

#include <vector>
#include <unordered_map>
#include "Box2D/Box2D.h"
#include "Tire.h"
#include "Health.h"
#include "Entity.h"

class Car : public Entity {
private:
    std::string id;
    b2RevoluteJoint* frontLeftJoint;
    b2RevoluteJoint* frontRightJoint;
    std::vector<Tire*> tires;
    Health health;
    int carCollisionDamage;
    int actualSurface;
    b2Vec2 lastPosOnTrack;
    b2Vec2 respawnPosition;
    float respawnAngle;

public:
    Car(std::string id, b2Body* body,
        b2Vec2 startingPosition,
        std::vector<Tire*> tires,
        int carCollisionDamage,
        b2RevoluteJoint* flJoint,
        b2RevoluteJoint* frJoint);

    void updateFriction();

    void updateMove(std::vector<char>& actions);

    void beginCollision(Entity* entity) override;

    void endCollision(Entity* object) override;

    void receiveHealing(int healingPoints);

    void receiveDamage(int damagePoints);

    void setTiresFriction(float newFriction);

    void setMaxForwardSpeed(float newMaxForwardSpeed);

    int getHealth();

    void updateSurface(int surface);

    void setLastPosOnTrack(b2Vec2 position);

    void setRespawnCoordinates(b2Vec2 position, float angle);

    std::string& getId();

    ~Car();
};

#endif //TESTING_CAR_H
