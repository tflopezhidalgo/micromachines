//
// Created by eliana on 19/10/19.
//

#include "Border.h"
#include "Box2D/Box2D.h"

Border::Border(b2World *world, float pos_x, float pos_y, float box_x, float box_y) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(pos_x, pos_y);
    // bodyDef.position = {x, y};
    body = world->CreateBody(&bodyDef);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(box_x, box_y);
    b2Fixture* fixture = body->CreateFixture(&polygonShape, 0.1f);

    body->SetUserData(this);


}
