//
// Created by leobellaera on 22/10/19.
//

#include "World.h"

#define BOX_SIZE 20
#define STONE_SIZE 10

#define FPS_KEY "framesPerSecond"

World::World(float height, float width, std::map<std::string, float> &config) :
    height(height),
    width(width),
    config(config) {
    world = new b2World({0.f, 0.f});
    world->SetContactListener(&collisionsProcessor);
    //b2Body* leftLimitBody = addBody(width/2);
    //agregar bordes del mapa
}

//private method that generates a new body in the physical world
b2Body* World::addBody(b2Vec2 pos, bool dynamic) {
    b2BodyDef bodyDef;
    if (dynamic) {
        bodyDef.type = b2_dynamicBody;
    } else {
        bodyDef.type = b2_staticBody;
    }
    bodyDef.position = pos;
    b2Body* body = world->CreateBody(&bodyDef);
    return body;
}

b2Body* World::addBox(b2Vec2 pos, b2Vec2 size, bool dynamic) {
    b2Body* boxBody = addBody(pos, dynamic);
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x / 2, size.y / 2);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygonShape;
    fixture_def.density = 1.f; //density should be variable
    fixture_def.isSensor = true;
    boxBody->CreateFixture(&fixture_def);

    return boxBody;
}

HealthBooster* World::addHealthBooster(float x_pos, float y_pos) {
    b2Body* body = addBox({x_pos, y_pos},
                             {BOX_SIZE, BOX_SIZE}, false);
    HealthBooster* healthBooster = new HealthBooster(body);
    body->SetUserData(healthBooster);
    return healthBooster;
}

Car* World::addCar(float x_pos, float y_pos) {
    //stage tendra un hash con carId como clave de la forma (carId, Car)
    b2Body* body = addBody({x_pos, y_pos}, true);
    Car* car = new Car(world, body, config);
    body->SetUserData(car);
    return car;
}

void World::step() {
    float timeStep = 1.f / config.find(FPS_KEY)->second;
    int velocityIterations = 8;
    int positionIterations = 3; //should be 3
    world->Step(timeStep, velocityIterations, positionIterations);
    //world->ClearForces(); neccesary?
}

World::~World() {
    b2Body* bodies = world->GetBodyList();
    while (bodies) {
        b2Body* actualBody = bodies;
        bodies = bodies->GetNext();
        world->DestroyBody(actualBody);
    }
}
