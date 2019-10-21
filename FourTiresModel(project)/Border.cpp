//
// Created by eliana on 19/10/19.
//

#include "Border.h"
#include "Box2D/Box2D.h"

Border::Border(b2World *world, b2Vec2 &pos, b2Vec2 &len) :
    type(CrashType::BORDER){
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(pos.x, pos.y);
    body = world->CreateBody(&bodyDef);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(len.x, len.y);
   // polygonShape.setFillColor(Color::Red);

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygonShape;
    fixture_def.density = 0.1f;
    fixture_def.isSensor = true;
    b2Fixture* fixture = body->CreateFixture(&fixture_def);

    body->SetUserData(this);
    fixture->SetUserData(this);
}

CrashType Border::getType() {
    return type;
}

void Border::getDamage(int damage) {
    // pass
}

Border::~Border() {
    body->GetWorld()->DestroyBody(body);
}
