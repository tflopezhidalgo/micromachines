#include "Health.h"

Health::Health() :
        actualHealth(100),
        maximumHealth(100) {}

void Health::receiveDamage(int damagePoints) {
    if (actualHealth - damagePoints < 0) {
        actualHealth = 0;
    } else {
        actualHealth -= damagePoints;
    }
}

void Health::receiveHealing(int healingPoints) {
    if (actualHealth + healingPoints > maximumHealth) {
        actualHealth = maximumHealth;
    } else {
        actualHealth += healingPoints;
    }
}

bool Health::isDead() {
    return (actualHealth == 0);
}

int Health::getHealth() {
    return actualHealth;
}
