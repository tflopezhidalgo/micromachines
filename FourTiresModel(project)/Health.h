//
// Created by leobellaera on 13/10/19.
//

#ifndef MICROMACHINES_HEALTH_H
#define MICROMACHINES_HEALTH_H

class Health {
private:
    int health;
public:
    Health(int initialHealth);
    void receiveDamage(int damage);
    void receiveHealing(int healingPoints);
    bool isDead();
};

#endif //MICROMACHINES_HEALTH_H
