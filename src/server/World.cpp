//
// Created by leobellaera on 22/10/19.
//

#include "World.h"
#include "Constants.h"

#define ANGULAR_DAMPING 5
#define DEGTORAD 0.017453292f

World::World(float height, float width, std::map<std::string, float> &config) :
    height(height),
    width(width),
    timeStep(1.f / config.find(FPS_KEY)->second),
    config(config) {
    world = new b2World({0.f, 0.f});
    world->SetContactListener(&collisionsProcessor);

    //edges addition

    b2Vec2 horizontalEdgeSize = {width, EDGE_THICKNESS};
    b2Vec2 verticalEdgeSize = {EDGE_THICKNESS, height};

    //top edge
    addBoxBody({0.f, height / 2.f}, horizontalEdgeSize, false, false);

    //down edge
    addBoxBody({0.f, -height / 2.f}, horizontalEdgeSize, false, false);

    //left edge
    addBoxBody({-width / 2.f, 0.f}, verticalEdgeSize, false, false);

    //right edge
    addBoxBody({width / 2.f, 0.f}, verticalEdgeSize, false, false);
}

//private method that generates a new body in the physical world
b2Body* World::addBody(b2Vec2 pos, bool dynamic, float angle) {
    b2BodyDef bodyDef;
    if (dynamic) {
        bodyDef.type = b2_dynamicBody;
    } else {
        bodyDef.type = b2_staticBody;
    }
    bodyDef.position = pos;
    bodyDef.angle = angle*DEGTORAD;
    b2Body* body = world->CreateBody(&bodyDef);
    return body;
}

b2Body* World::addBoxBody(b2Vec2 pos, b2Vec2 size, bool dynamic, bool sensor, float angle) {
    b2Body* boxBody = addBody(pos, dynamic, angle);
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x / 2.f, size.y / 2.f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygonShape;
    fixture_def.density = 1.f;
    fixture_def.isSensor = sensor;
    boxBody->CreateFixture(&fixture_def);

    return boxBody;
}

b2Body* World::addCircleBody(b2Vec2 pos, float radius, bool dynamic, bool sensor) {
    b2Body* body = addBody(pos, dynamic);
    b2CircleShape circle;
    circle.m_p.Set(0, 0);
    circle.m_radius = radius;

    b2FixtureDef fixture_def;
    fixture_def.shape = &circle;
    fixture_def.isSensor = sensor;
    body->CreateFixture(&fixture_def);

    return body;
}

HealthBooster* World::addHealthBooster(float x_pos, float y_pos) {
    b2Body* body = addCircleBody({x_pos, y_pos}, BOOSTERS_RADIUS, false, true);
    auto healthBooster = new HealthBooster(body, int(config.find(HEALTH_BOOST_KEY)->second));
    body->SetUserData(healthBooster);
    return healthBooster;
}

SpeedBooster* World::addSpeedBooster(float x_pos, float y_pos) {
    b2Body* body = addCircleBody({x_pos, y_pos}, BOOSTERS_RADIUS, false, true);
    auto speedBooster = new SpeedBooster(body,
            config.find(SPEED_BOOST_KEY)->second,
            config.find(MAX_FORWARD_SPEED_KEY)->second);
    return speedBooster;
}

Oil* World::addOil(float x_pos, float y_pos) {
    b2Body* body = addCircleBody({x_pos, y_pos}, OIL_RADIUS, false, true);
    auto oil = new Oil(body, config.find(OIL_GRIP_KEY)->second);
    body->SetUserData(oil);
    return oil;
}

Stone* World::addStone(float x_pos, float y_pos) {
    b2Body* body = addCircleBody({x_pos, y_pos}, STONE_RADIUS, false, false);
    auto stone = new Stone(body, int(config.find(STONE_DAMAGE_KEY)->second));
    body->SetUserData(stone);
    return stone;
}

Car* World::addCar(std::string id, float x_pos, float y_pos, float angle) {
    //todo use x_pos, y_pos
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {x_pos, y_pos};
    //bodyDef.angle = angle*DEGTORAD;
    b2Body* carBody = world->CreateBody(&bodyDef);

    carBody->SetAngularDamping(ANGULAR_DAMPING);

    float carWidth = float(CAR_W) / 2.f;
    float carHeight = float(CAR_H) / 2.f;
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(carWidth, carHeight);
    carBody->CreateFixture(&polygonShape, 0.1f);

    //common joint parameters
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = carBody;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = 0;
    jointDef.upperAngle = 0;
    jointDef.localAnchorB.SetZero(); //tire centre

    std::vector<Tire*> tires;

    float maxForwardSpeed = config.find(MAX_FORWARD_SPEED_KEY)->second;
    float maxBackwardSpeed = config.find(MAX_BACKWARD_SPEED_KEY)->second;
    float backTireMaxDriveForce = config.find(BACK_MAX_DRIVE_FORCE_KEY)->second;
    float frontTireMaxDriveForce = config.find(FRONT_MAX_DRIVE_FORCE_KEY)->second;
    float backTireMaxLatImpulse = config.find(BACK_MAX_LAT_IMPULSE_KEY)->second;
    float frontTireMaxLatImpulse = config.find(FRONT_MAX_LAT_IMPULSE_KEY)->second;
    float initialFriction = config.find(TRACK_FRICTION_KEY)->second;

    //back left tire
    b2Vec2 backLeftTirePosition = {-3, -6.f};
    b2Body* body = createTireBody({x_pos, y_pos}, backLeftTirePosition, angle);
    Tire* tire = new Tire(body, maxForwardSpeed, maxBackwardSpeed,
            backTireMaxDriveForce, backTireMaxLatImpulse, initialFriction);
    joinTireToChassis(&jointDef, body, backLeftTirePosition);
    tires.push_back(tire);

    //back right tire
    b2Vec2 backRightTirePosition = {3, -6.f};
    body = createTireBody({x_pos, y_pos}, backRightTirePosition, angle);
    tire = new Tire(body, maxForwardSpeed, maxBackwardSpeed,
            backTireMaxDriveForce, backTireMaxLatImpulse, initialFriction);
    joinTireToChassis(&jointDef, body, backRightTirePosition);
    tires.push_back(tire);

    //front left tire
    b2Vec2 frontLeftTirePosition = {-3, 6.f};
    body = createTireBody({x_pos, y_pos}, frontLeftTirePosition, angle);
    tire = new Tire(body, maxForwardSpeed, maxBackwardSpeed,
            frontTireMaxDriveForce, frontTireMaxLatImpulse, initialFriction);
    b2RevoluteJoint* flJoint = joinTireToChassis(&jointDef, body, frontLeftTirePosition);
    tires.push_back(tire);

    //front right tire
    b2Vec2 frontRightTirePosition = {3, 6.f};
    body = createTireBody({x_pos, y_pos}, frontRightTirePosition, angle);
    tire = new Tire(body, maxForwardSpeed, maxBackwardSpeed,
                    frontTireMaxDriveForce, frontTireMaxLatImpulse, initialFriction);
    b2RevoluteJoint* frJoint = joinTireToChassis(&jointDef, body, frontRightTirePosition);
    tires.push_back(tire);

    Car* car = new Car(id, carBody, tires,
            int(config.find(CAR_COLLISION_DAMAGE_KEY)->second), flJoint, frJoint);
    carBody->SetUserData(car);
    return car;
}

b2Body* World::addFloorBody(b2Vec2 pos, b2Vec2 size) {
    b2Body* boxBody = addBody(pos, false);
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x / 2.f, size.y / 2.f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygonShape;
    fixture_def.isSensor = true;
    boxBody->CreateFixture(&fixture_def);

    return boxBody;
}

//actually, vertical and horizontal tracks have the same shape
Floor* World::addFloor(float x_pos, float y_pos, float friction) {
    b2Body* body = addFloorBody({x_pos, y_pos}, {TILE_WIDTH, TILE_HEIGHT});
    auto floor = new Floor(body, friction);
    body->SetUserData(floor);
    return floor;
}

b2Body* World::getGrandstandBody(float x_pos, float y_pos, bool horizontalDisposal) {
    b2Body* body;
    if (horizontalDisposal) {
        body = addBoxBody({x_pos, y_pos},{GRANDSTAND_WIDTH, GRANDSTAND_HEIGHT},
                false, false);
    } else {
        body = addBoxBody({x_pos, y_pos},{GRANDSTAND_HEIGHT, GRANDSTAND_WIDTH},
                          false, false);
    }
    return body;
}

Projectile* World::addProjectile(EntityIdentifier entityIdentifier, float x_pos, float y_pos) {
    b2Body* body = addCircleBody({x_pos, y_pos}, PROJECTILE_RADIUS, true, false);
    Projectile* projectile = new Projectile(entityIdentifier, body);
    return projectile;
}

Checkpoint* World::addCheckpoint(float x_pos, float y_pos, bool horizontalDisposal,
                                 int checkpointOrder, RaceJudge& raceJudge) {
    b2Vec2 size;
    if (horizontalDisposal) {
        size = {TILE_WIDTH, float(TILE_HEIGHT)/3.f};
    } else {
        size = {float(TILE_WIDTH)/3.f, TILE_HEIGHT};
    }
    b2Body* body = addBoxBody({x_pos, y_pos}, size, false, true);

    Checkpoint* checkpoint = new Checkpoint(body, checkpointOrder, raceJudge);
    body->SetUserData(checkpoint);

    return checkpoint;
}

b2Body* World::createTireBody(b2Vec2 chassisPosition, b2Vec2 tirePos, float angle) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {chassisPosition.x + tirePos.x, chassisPosition.y + tirePos.y};
    //bodyDef.angle = angle*DEGTORAD;

    b2Body* body = world->CreateBody(&bodyDef);
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox( 0.5f, 1.25f );

    body->CreateFixture(&polygonShape, 1);
    return body;
}

b2RevoluteJoint* World::joinTireToChassis(
        b2RevoluteJointDef* jointDef,
        b2Body* tireBody, b2Vec2& pos) {
    jointDef->bodyB = tireBody;
    jointDef->localAnchorA.Set(pos.x, pos.y);
    auto joint = (b2RevoluteJoint*)world->CreateJoint(jointDef);
    return joint;
}

void World::step() {
    int velocityIterations = 8;
    int positionIterations = 3;
    world->Step(timeStep, velocityIterations, positionIterations);
}

World::~World() {
    b2Body* bodies = world->GetBodyList();
    while (bodies) {
        b2Body* actualBody = bodies;
        bodies = bodies->GetNext();
        world->DestroyBody(actualBody);
    }
    delete world;
}
