//
// Created by eliana on 20/10/19.
//

#include "Stone.h"

Stone::Stone(b2World *world, b2Vec2 &pos) {
    type(CrashType::STONE) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);
    body = world->CreateBody(&bodyDef);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(2.f, 2.f);
    // obtener la longitud de algun config

    b2FixtureDef fixture_def;
    fixture_def.shape = &polygonShape;
    fixture_def.density = 100.f;
    fixture_def.friction = 100.f;
    //fixture_def.isSensor = true;
    b2Fixture* fixture = body->CreateFixture(&fixture_def);

    body->SetUserData(this);
    fixture->SetUserData((void*)this);
}

const b2Vec2& Stone::getPosition() {
    return body->GetPosition();
}

CrashType Stone::get_type() {
    return type;
}
