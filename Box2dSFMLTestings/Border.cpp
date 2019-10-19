//
// Created by eliana on 19/10/19.
//

#include "Border.h"
#include "Box2D/Box2D.h"

Border::Border(b2World *world, int x, int y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2BodyType::b2_staticBody;
    bodyDef.position = {x, y};
    body = world->CreateBody(&bodyDef);

    b2PolygonShape polygon;
    polygon.SetAsBox(50, 50);

    b2Fixture* fix_borde;
    b2FixtureDef fix_bordeDef;
    fix_bordeDef.shape = polygon;
    fix_bordeDef.density = 1.f;
    fix_bordeDef.friction = 0.2f;
    fix_bordeDef.restitution = 0.f;

    body->CreateFixture(&fix_borderDef);
    body->SetUserData(this);


}
