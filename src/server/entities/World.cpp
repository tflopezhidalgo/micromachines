//
// Created by leobellaera on 22/10/19.
//

#include "World.h"

#define ANGULAR_DAMPING 3
#define BOX_SIZE 20
#define STONE_SIZE 10

/* obtener config.file
#define BOX_SIZE "boxSize"
#define STONE_SIZE "stoneSize"
#define OILFRICTION "oilFriction"
*/

#define FLOOR_OIL_SIZE "oilSize"

#define CURVE_SIZE "curveSize"
#define CURVE_RADIUS "curveRadius"

#define DEGTORAD 20 // no se cual es un buen valor
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
    //fixture_def.isSensor = true;
    boxBody->CreateFixture(&fixture_def);

    return boxBody;
}

HealthBooster* World::addHealthBooster(float x_pos, float y_pos) {
    // float box_size = config.find(BOX_SIZE)->second;
    b2Body* body = addBox({x_pos, y_pos},
                             {BOX_SIZE, BOX_SIZE}, false);
    HealthBooster* healthBooster = new HealthBooster(body);
    body->SetUserData(healthBooster);
    return healthBooster;
}

Stone* World::addStone(float x_pos, float y_pos) {
    // float stone_size = config.find(STONE_SIZE)->second;
    b2Body* body = addBox({x_pos, y_pos}, {STONE_SIZE, STONE_SIZE}, false);
    auto stone = new Stone(body);
    body->SetUserData(stone);
    return stone;
}

Car* World::addCar(float x_pos, float y_pos) {
    //stage tendra un hash con carId como clave de la forma (carId, Car)
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
    joinTireToChassis(world, &jointDef, body, {-3.f, 0.75f});
    tires.push_back(tire);

    //back right tire
    body = createTireBody();
    tire = new Tire(body, config);
    joinTireToChassis(world, &jointDef, body, {3.f, 0.75f});
    tires.push_back(tire);

    //front left tire
    body = createTireBody();
    tire = new Tire(body, config);
    b2RevoluteJoint* flJoint = joinTireToChassis(world, &jointDef, body, {-3.f, 13.5f});
    tires.push_back(tire);

    //front right tire
    body = createTireBody();
    tire = new Tire(body, config);
    b2RevoluteJoint* frJoint = joinTireToChassis(world, &jointDef, body, {3.f, 13.5f});
    tires.push_back(tire);

    Car* car = new Car(carBody, tires, flJoint, frJoint);
    carBody->SetUserData(car);
    return car;
}

b2Body* World::addFloor(b2Vec2 pos, b2Vec2 size, bool dynamic) {
    b2Body* boxBody = addBody(pos, dynamic);
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x / 2, size.y / 2);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygonShape;
    //fixture_def.density = 0.f; // textura del piso, se tiene que atravezar
    //fixture_def.friction = 0.9f; // para que vaya mas lento
    fixture_def.isSensor = true;
    boxBody->CreateFixture(&fixture_def);

    return boxBody;
}

b2Body* World::addCurve(b2Vec2 pos, float radius, b2Vec2 size, bool dynamic) {
    b2Vec2 vertices[8];
    vertices[0].Set(0,size.y); // deberia ser el contrario de la esquina
    for (int i = 0; i < 7; i++) {
        float angle = i / 6.0 * 90 * DEGTORAD;
        vertices[i+1].Set( radius * cosf(angle), radius * sinf(angle) );
    }
    b2Body* curveBody = addBody(pos, dynamic);
    b2FixtureDef fixture_def;
    b2PolygonShape polygonShape;
    polygonShape.Set(vertices, 8);
    fixture_def.shape = &polygonShape;
    fixture_def.isSensor = true;
    curveBody->CreateFixture(&fixture_def);

    // make the body rotate at 45 degrees per second
    //curveBody->SetAngularVelocity(45 * DEGTORAD);
    return curveBody;
}

Curve* World::addStreetCurve(float x_pos, float y_pos) {
    float curveSize = config.find(CURVE_SIZE)->second;
    float radius = config.find(CURVE_RADIUS)->second;
    b2Body* body = addCurve({x_pos, y_pos}, radius, {curveSize, curveSize}, false);
    Curve *curve = new Curve(body);
    body->SetUserData(curve);
    return curve;
}

Oil* World::addOil(float x_pos, float y_pos) {
    float oilSize = config.find(FLOOR_OIL_SIZE)->second;
    b2Body* body = addFloor({x_pos, y_pos}, {oilSize, oilSize}, false);
    Oil *oil = new Oil(OIL, body, config);
    body->SetUserData(oil);
    return oil;
}

void World::step() {
    float timeStep = 1.f / config.find(FPS_KEY)->second;
    int velocityIterations = 8;
    int positionIterations = 3; //should be 3
    world->Step(timeStep, velocityIterations, positionIterations);
    //world->ClearForces(); neccesary?
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
    fixture_def.isSensor = true;
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

b2RevoluteJoint* World::joinTireToChassis(b2World* world,
                                            b2RevoluteJointDef* jointDef,
                                            b2Body* tireBody, b2Vec2 pos) {
    jointDef->bodyB = tireBody;
    jointDef->localAnchorA.Set(pos.x, pos.y);
    auto joint = (b2RevoluteJoint*)world->CreateJoint(jointDef);
    return joint;
}

World::~World() {
    b2Body* bodies = world->GetBodyList();
    while (bodies) {
        b2Body* actualBody = bodies;
        bodies = bodies->GetNext();
        world->DestroyBody(actualBody);
    }
}
