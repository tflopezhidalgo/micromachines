//
// Created by leobellaera on 22/10/19.
//

#include "World.h"
#include "Macros.h"

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
    addBox({0.f, height/2.f}, horizontalEdgeSize, false, false);

    //down edge
    addBox({0.f, -height/2.f}, horizontalEdgeSize, false, false);

    //left edge
    addBox({-width/2.f, 0.f}, verticalEdgeSize, false, false);

    //right edge
    addBox({width/2.f, 0.f}, verticalEdgeSize, false, false);
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

b2Body* World::addBox(b2Vec2 pos, b2Vec2 size, bool dynamic, bool sensor) {
    b2Body* boxBody = addBody(pos, dynamic);
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(size.x / 2.f, size.y / 2.f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygonShape;
    fixture_def.density = 1.f;
    fixture_def.isSensor = sensor;
    boxBody->CreateFixture(&fixture_def);

    return boxBody;
}

b2Body* World::addCircle(b2Vec2 pos, float radius, bool dynamic, bool sensor) {
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
    b2Body* body = addCircle({x_pos, y_pos}, BOOSTERS_RADIUS, false, true);
    auto healthBooster = new HealthBooster(body, int(config.find(HEALTH_BOOST_KEY)->second));
    body->SetUserData(healthBooster);
    return healthBooster;
}

SpeedBooster* World::addSpeedBooster(float x_pos, float y_pos) {
    b2Body* body = addCircle({x_pos,y_pos}, BOOSTERS_RADIUS, false, true);
    auto speedBooster = new SpeedBooster(body,
            config.find(SPEED_BOOST_KEY)->second,
            config.find(MAX_FORWARD_SPEED_KEY)->second);
    return speedBooster;
}

Oil* World::addOil(float x_pos, float y_pos) {
    b2Body* body = addCircle({x_pos, y_pos}, OIL_RADIUS, false, true);
    auto oil = new Oil(body, config.find(OIL_GRIP_KEY)->second);
    body->SetUserData(oil);
    return oil;
}

Stone* World::addStone(float x_pos, float y_pos) {
    b2Body* body = addCircle({x_pos, y_pos}, STONE_RADIUS, false, false);
    auto stone = new Stone(body, int(config.find(STONE_DAMAGE_KEY)->second));
    body->SetUserData(stone);
    return stone;
}

Car* World::addCar(float x_pos, float y_pos) {
    //todo use x_pos, y_pos
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    b2Body* carBody = world->CreateBody(&bodyDef);

    carBody->SetAngularDamping(ANGULAR_DAMPING);
    b2Vec2 vertices[4];
    vertices[0].Set(-3,   -7.5f);
    vertices[1].Set(3, -7.5f);
    vertices[2].Set(-3, 7.5f);
    vertices[3].Set(3,  7.5f);
    b2PolygonShape polygonShape;
    polygonShape.Set(vertices, 4);
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
    float defaultFriction = config.find(DEFAULT_FRICTION_KEY)->second;

    //back left tire
    b2Vec2 backLeftTirePosition = {-3, -6.f};
    b2Body* body = createTireBody(backLeftTirePosition);
    Tire* tire = new Tire(body, maxForwardSpeed, maxBackwardSpeed,
            backTireMaxDriveForce, backTireMaxLatImpulse, defaultFriction);
    joinTireToChassis(&jointDef, body, backLeftTirePosition);
    tires.push_back(tire);

    //back right tire
    b2Vec2 backRightTirePosition = {3, -6.f};
    body = createTireBody(backRightTirePosition);
    tire = new Tire(body, maxForwardSpeed, maxBackwardSpeed,
            backTireMaxDriveForce, backTireMaxLatImpulse, defaultFriction);
    joinTireToChassis(&jointDef, body, backRightTirePosition);
    tires.push_back(tire);

    //front left tire
    b2Vec2 frontLeftTirePosition = {-3, 6.f};
    body = createTireBody(frontLeftTirePosition);
    tire = new Tire(body, maxForwardSpeed, maxBackwardSpeed,
            frontTireMaxDriveForce, frontTireMaxLatImpulse, defaultFriction);
    b2RevoluteJoint* flJoint = joinTireToChassis(&jointDef, body, frontLeftTirePosition);
    tires.push_back(tire);

    //front right tire
    b2Vec2 frontRightTirePosition = {3, 6.f};
    body = createTireBody(frontRightTirePosition);
    tire = new Tire(body, maxForwardSpeed, maxBackwardSpeed,
                    frontTireMaxDriveForce, frontTireMaxLatImpulse, defaultFriction);
    b2RevoluteJoint* frJoint = joinTireToChassis(&jointDef, body, frontRightTirePosition);
    tires.push_back(tire);

    Car* car = new Car(carBody, tires,
            int(config.find(CAR_COLLISION_DAMAGE_KEY)->second),
            flJoint, frJoint);
    carBody->SetUserData(car);
    return car;
}

b2Body* World::addRectangularFloor(b2Vec2 pos, b2Vec2 size) {
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
Track* World::addTrack(float x_pos, float y_pos, int shape) {
    b2Body* body = addRectangularFloor({x_pos, y_pos}, {TRACK_SIZE, TRACK_SIZE});
    auto track = new Track(body, config.find(TRACK_FRICTION_KEY)->second);
    body->SetUserData(track);
    return track;
}

b2Body* World::createTireBody(b2Vec2& position) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position;

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

void World::destroyBody(b2Body* body) {
    world->DestroyBody(body);
}

World::~World() {
    b2Body* bodies = world->GetBodyList();
    while (bodies) {
        b2Body* actualBody = bodies;
        bodies = bodies->GetNext();
        world->DestroyBody(actualBody);
    }
}
