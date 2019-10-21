//
// Created by leobellaera on 18/10/19.
//

#ifndef TESTING_CAR_H
#define TESTING_CAR_H

#include <vector>
#include "CrashObject.h"
#include "Box2D/Box2D.h"
#include "Tire.h"

class Car : public CrashObject {
private:
    b2Body* body;
    std::vector<Tire*> tires;
    b2RevoluteJoint *flJoint, *frJoint;
    CrashType type;
    int health;
    bool is_dead;
public:
    Car(b2World* world, float  pos_x, float pos_y, CrashType type);
    //Car(b2World* world, b2Vec2 pos, CrashType type);
    void update(int key);
    const b2Vec2 getPosition();
    float getAngle();
    void getDamage(int damage) override;
    bool isDead();
    ~Car();

    CrashType getType();
};

#endif //TESTING_CAR_H
