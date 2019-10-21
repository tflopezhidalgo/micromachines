//
// Created by eliana on 19/10/19.
//

#include "CrashObject.h"

void CrashObject::getDamage(int damage) {
    health -= damage;
}

CrashType CrashObject::getType() {
    return type;
}

const b2Vec2 CrashObject::getPosition() {
    return b2Vec2();
}
