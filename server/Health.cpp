//
// Created by leobellaera on 13/10/19.
//

#include "Health.h"

Health::Health(int initialHealth) : //throw exception if health < 0
    health(initialHealth) {}

void Health::receiveDamage(int damagePoints) {
    health -= damagePoints;
}

void Health::receiveHealing(int healingPoints) {
    health += healingPoints;
}

bool Health::isDead() {
    return (health < 0);
}
