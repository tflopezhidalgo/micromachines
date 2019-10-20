//
// Created by eliana on 19/10/19.
//

#include "CrashObject.h"

void CrashObject::getDamage(int damage) {
    health = health - damage;
}

CrashType CrashObject::getType() {
    return type;
}
