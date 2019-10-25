//
// Created by leobellaera on 13/10/19.
//

#ifndef MICROMACHINES_HEALTH_H
#define MICROMACHINES_HEALTH_H

class Health {
private:
    int actualHealth;
    int maximumHealth;
public:
    Health(int initialHealth);
    void receiveDamage(int damage);
    void receiveHealing(int healingPoints);
    int getHealth();
    bool isDead();
};

#endif //MICROMACHINES_HEALTH_H
