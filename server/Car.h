//
// Created by leobellaera on 12/10/19.
//

#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include "Health.h"

class Car {
private:
    /*int angle;
    //int maxSpeed;
    int acceleration;
    int grab;
    int maneuverability;*/
    Health health;
    int x_pos;
    int y_pos;
public:
    Car(int initialHealth);
    void move(int side);
    void receiveDamage(int damagePoints);
    void receiveHealing(int healingPoints);
    bool isDead();
    ~Car();
};

#endif //MICROMACHINES_CAR_H
