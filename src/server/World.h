//
// Created by leobellaera on 22/10/19.
//

#ifndef TESTING_WORLD_H
#define TESTING_WORLD_H

#include <map>
#include <vector>
#include "Box2D/Box2D.h"
#include "entities/Car.h"
#include "entities/HealthBooster.h"
#include "entities/CollisionsProcessor.h"
#include "entities/Stone.h"
#include "entities/Oil.h"
#include "entities/SpeedBooster.h"
#include "entities/Floor.h"
#include "Identifiers.h"
#include "entities/GrandStand.h"
#include "entities/Checkpoint.h"

class World {
private:
    b2World* world;
    CollisionsProcessor collisionsProcessor;
    float height;
    float width;
    float timeStep;
    std::map<std::string, float> &config;

    b2Body* addBody(b2Vec2 pos, bool dynamic, float angle = 0);

    b2Body* addBoxBody(b2Vec2 pos, b2Vec2 size, bool dynamic, bool sensor, float angle = 0);

    b2Body* addCircleBody(b2Vec2 pos, float radius, bool dynamic, bool sensor);

    b2Body* addFloorBody(b2Vec2 pos, b2Vec2 size);

    b2Body* createTireBody(b2Vec2 chassisPosition, b2Vec2 tirePos, float angle) ;

    b2RevoluteJoint* joinTireToChassis(b2RevoluteJointDef* jointDef,
            b2Body* tireBody, b2Vec2& pos);

public:
    World(float height, float width, std::map<std::string, float> &config);

    Car* addCar(std::string id, float x_pos, float y_pos, float angle);

    GrandStand* addGrandStand(float x_pos, float y_pos, float angle);

    void addCheckpoint(float x_pos, float y_pos,
            bool horizontalDisposal, int checkpointOrder, RaceJudge& raceJudge);

    HealthBooster* addHealthBooster(float x_pos, float y_pos);

    Stone* addStone(float x_pos, float y_pos);

    SpeedBooster* addSpeedBooster(float x_pos, float y_pos);

    Oil* addOil(float x_pos, float y_pos);

    Floor* addFloor(float x_pos, float y_pos, float friction);

    void destroyBody(b2Body* body);

    void step();

    ~World();
};

#endif //TESTING_WORLD_H
