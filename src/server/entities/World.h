//
// Created by leobellaera on 22/10/19.
//

#ifndef TESTING_WORLD_H
#define TESTING_WORLD_H

#include <map>
#include <vector>
#include "Box2D/Box2D.h"
#include "Car.h"
#include "HealthBooster.h"
#include "CollisionsProcessor.h"
#include "Stone.h"
#include "Curve.h"
#include "Oil.h"
#include "SpeedBooster.h"

class World {
private:
    b2World* world;
    CollisionsProcessor collisionsProcessor;
    float height;
    float width;
    std::map<std::string, float> &config;

    b2Body* addBody(b2Vec2 pos, bool dynamic);

    b2Body* addBox(b2Vec2 pos, b2Vec2 size, bool dynamic);

    void createCarChassisFixture(b2Body* body);

    b2Body* createTireBody();

    b2RevoluteJoint* joinTireToChassis(b2RevoluteJointDef* jointDef,
            b2Body* tireBody, b2Vec2 pos);

    b2Body *addFloor(b2Vec2 pos, b2Vec2 size, bool dynamic);

    b2Body *addCurve(b2Vec2 pos, float radius, b2Vec2 size, bool dynamic);
public:
    World(float height, float width, std::map<std::string, float> &config);

    Car* addCar(float x_pos, float y_pos);

    HealthBooster* addHealthBooster(float x_pos, float y_pos);

    Stone* addStone(float x_pos, float y_pos);

    Oil *addOil(float x_pos, float y_pos);
    SpeedBooster* addSpeedBooster(float x_pos, float y_pos);

    b2Body* addFloor(b2Vec2 pos, b2Vec2 size);
    Curve* addStreetCurve(float x_pos, float y_pos);

    b2Body* addCurve(b2Vec2 pos, float radius, b2Vec2 size);

    //addVerticalTrack
    //addHorizontalTrack

    void step();

    ~World();
};

#endif //TESTING_WORLD_H

