//
// Created by leobellaera on 22/10/19.
//

#include "World.h"

#define ANGULAR_DAMPING 3
#define BOX_SIZE 1
#define STONE_SIZE 0.5f
#define FLOOR_OIL_SIZE 2
#define CURVE_SIZE 10
#define CURVE_RADIUS 5

#define FPS "framesPerSecond"

#define DEGTORAD 20 //no se cual es un buen valor

World::World(float height, float width, std::map<std::string, float> &config) :
    height(height),
    width(width),
    timeStep(1.f / config.find(FPS)->second),
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
    fixture_def.density = 1.f;
    boxBody->CreateFixture(&fixture_def);

    return boxBody;
}

HealthBooster* World::addHealthBooster(float x_pos, float y_pos) {
    b2Body* body = addBox({x_pos, y_pos},
                             {BOX_SIZE, BOX_SIZE}, false);
    auto healthBooster = new HealthBooster(body, config);
    body->SetUserData(healthBooster);
    return healthBooster;
}

Stone* World::addStone(float x_pos, float y_pos) {
    b2Body* body = addBox({x_pos, y_pos}, {STONE_SIZE, STONE_SIZE}, false);
    auto stone = new Stone(body, config);
    body->SetUserData(stone);
    return stone;
}

Car* World::addCar(float x_pos, float y_pos) {
    b2Body* carBody = addBody({x_pos, y_pos}, true);
    carBody->SetAngularDamping(ANGULAR_DAMPING);
    createCarChassisFixture(carBody);

    b2RevoluteJointDef jointDef;
    jointDef.bodyA = carBody;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0;
    jointDef.upperAngle = 0;
    jointDef.localAnchorB.SetZero();

    std::vector<Tire*> tires;

    b2Body* body = createTireBody();
    Tire* tire = new Tire(body, config);
    joinTireToChassis(&jointDef, body, {-3.f, 0.75f});
    tires.push_back(tire);

    //back right tire
    body = createTireBody();
    tire = new Tire(body, config);
    joinTireToChassis(&jointDef, body, {3.f, 0.75f});
    tires.push_back(tire);

    //front left tire
    body = createTireBody();
    tire = new Tire(body, config);
    b2RevoluteJoint* flJoint = joinTireToChassis(&jointDef, body, {-3.f, 13.5f});
    tires.push_back(tire);

    //front right tire
    body = createTireBody();
    tire = new Tire(body, config);
    b2RevoluteJoint* frJoint = joinTireToChassis(&jointDef, body, {3.f, 13.5f});
    tires.push_back(tire);

    Car* car = new Car(carBody, tires, flJoint, frJoint);
    carBody->SetUserData(car);
    return car;
}

b2Body* World::addFloor(b2Vec2 pos, b2Vec2 size) {
    b2Body* boxBody = addBody(pos, false);
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x / 2, size.y / 2);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygonShape;
    fixture_def.isSensor = true;
    boxBody->CreateFixture(&fixture_def);

    return boxBody;
}

b2Body* World::addCurve(b2Vec2 pos, float radius, b2Vec2 size) {
    b2Vec2 vertices[8];
    vertices[0].Set(0,size.y); // deberia ser el contrario de la esquina
    for (int i = 0; i < 7; i++) {
        float angle = i / 6.0 * 90 * DEGTORAD;
        vertices[i+1].Set( radius * cosf(angle), radius * sinf(angle) );
    }
    b2Body* curveBody = addBody(pos, false);
    b2FixtureDef fixture_def;
    b2PolygonShape polygonShape;
    polygonShape.Set(vertices, 8);
    fixture_def.shape = &polygonShape;
    fixture_def.isSensor = true;
    curveBody->CreateFixture(&fixture_def);

    //make the body rotate at 45 degrees per second
    //curveBody->SetAngularVelocity(45 * DEGTORAD);
    return curveBody;
}

Curve* World::addStreetCurve(float x_pos, float y_pos) {
    b2Body* body = addCurve({x_pos, y_pos}, CURVE_RADIUS, {CURVE_SIZE, CURVE_SIZE});
    auto curve = new Curve(body);
    body->SetUserData(curve);
    return curve;
}

Oil* World::addOil(float x_pos, float y_pos) {
    b2Body* body = addFloor({x_pos, y_pos}, {FLOOR_OIL_SIZE, FLOOR_OIL_SIZE});
    auto oil = new Oil(body, config);
    body->SetUserData(oil);
    return oil;
}

SpeedBooster* World::addSpeedBooster(float x_pos, float y_pos) {
    b2Body* body = addBody({x_pos,y_pos}, false);
    auto speedBooster = new SpeedBooster(body, config);
    return speedBooster;
}

void World::createCarChassisFixture(b2Body* body) {
    b2Vec2 vertices[4];
    vertices[0].Set(-3,   0);
    vertices[1].Set(3, 0);
    vertices[2].Set(-3, 15);
    vertices[3].Set(3,  15);

    b2PolygonShape polygonShape;
    polygonShape.Set(vertices, 4);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygonShape;
    fixture_def.density = 0.01f;
    fixture_def.shape = &polygonShape;

    body->CreateFixture(&fixture_def);
}

b2Body* World::createTireBody() {
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(0.5f, 1.25f);
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    b2Body* body = world->CreateBody(&bodyDef);
    body->CreateFixture(&polygonShape, 1);
    return body;
}

b2RevoluteJoint* World::joinTireToChassis(
        b2RevoluteJointDef* jointDef,
        b2Body* tireBody, b2Vec2 pos) {
    jointDef->bodyB = tireBody;
    jointDef->localAnchorA.Set(pos.x, pos.y);
    auto joint = (b2RevoluteJoint*)world->CreateJoint(jointDef);
    return joint;
}

void World::step() {
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
