#ifndef TESTING_CAR_H
#define TESTING_CAR_H

#include <vector>
#include <unordered_map>
#include <TimedEvent.h>
#include <set>
#include "Box2D/Box2D.h"
#include "Tire.h"
#include "Health.h"
#include "Entity.h"

class TimedEvent;

class Car : public Entity {
private:
    std::string id;
    std::vector<TimedEvent>& timedEvents;
    b2RevoluteJoint* frontLeftJoint;
    b2RevoluteJoint* frontRightJoint;
    std::vector<Tire*> tires;
    Health health;
    int carCollisionDamage;
    int actualSurface;
    b2Vec2 lastPosOnTrack;
    b2Vec2 respawnPosition;
    float respawnAngle;
    bool reducedVision;
    bool forwardSpeedBoosted;
    bool lateralImpulseBoosted;

public:
    Car(std::string id, std::vector<TimedEvent>& timedEvents,
        b2Body* body, b2Vec2 startingPosition,
        std::vector<Tire*> tires, int carCollisionDamage,
        b2RevoluteJoint* flJoint, b2RevoluteJoint* frJoint);

    void updateFriction();

    void updateMove(std::vector<char>& actions);

    void beginCollision(Entity* entity) override;

    void endCollision(Entity* object) override;

    void receiveHealing(int healingPoints);

    void receiveDamage(int damagePoints);

    void recoverHealth();

    void setTiresFriction(float newFriction);

    void updateMaxForwardSpeed(float difference);

    void resetMaxForwardSpeed();

    void updateMaxLateralImpulse(float difference);

    void resetMaxLateralImpulse();

    int getHealth();

    float getSpeed();

    float getForwardSpeed();

    bool isDead() override;

    bool hasReducedVision();

    void reduceVision();

    void recoverTotalVision();

    void updateSurface(int surface);
    
    void updatePosition();

    void setLastPosOnTrack(b2Vec2 position);

    void setRespawnCoordinates(b2Vec2 position, float angle);

    std::string& getId();

    ~Car();
};

#endif //TESTING_CAR_H
