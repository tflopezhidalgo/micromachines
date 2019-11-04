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
#include "Oil.h"
#include "SpeedBooster.h"
#include "Track.h"
#include "../common/Identifiers.h"

class World {
private:
    b2World* world;
    CollisionsProcessor collisionsProcessor;
    float height;
    float width;
    float timeStep;
    std::map<std::string, float> &config;

    b2Body* addBody(b2Vec2 pos, bool dynamic);

    b2Body* addBox(b2Vec2 pos, b2Vec2 size, bool dynamic, bool sensor);

    b2Body* addCircle(b2Vec2 pos, float radius, bool dynamic, bool sensor);

    b2Body* addRectangularFloor(b2Vec2 pos, b2Vec2 size);

    b2Body* createTireBody(b2Vec2& position, b2Vec2 chassisPosition) ;

    b2RevoluteJoint* joinTireToChassis(b2RevoluteJointDef* jointDef,
            b2Body* tireBody, b2Vec2& pos);

public:
    World(float height, float width, std::map<std::string, float> &config);

    Car* addCar(float x_pos, float y_pos);

    HealthBooster* addHealthBooster(float x_pos, float y_pos);

    Stone* addStone(float x_pos, float y_pos);

    SpeedBooster* addSpeedBooster(float x_pos, float y_pos);

    Oil* addOil(float x_pos, float y_pos);

    Track* addTrack(float x_pos, float y_pos, int shape = 0);

    void destroyBody(b2Body* body);

    void step();

    ~World();

//    void removeEntity(Identifier identifier);
};

#endif //TESTING_WORLD_H
