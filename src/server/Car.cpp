//
// Created by leobellaera on 12/10/19.
//

#include "Car.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

Car::Car(int initialHealth) :
    health(health),
    x_pos(0),
    y_pos(0) {}

void Car::move(int side) {
    switch(side) {
        case UP:
            y_pos += 1;
        case DOWN:
            y_pos -= 1;
        case LEFT:
            x_pos -= 1;
        case RIGHT:
            x_pos += 1;
    }
}

void Car::receiveDamage(int damagePoints) {
    health.receiveDamage(damagePoints);
}

void Car::receiveHealing(int healingPoints) {
    health.receiveHealing(healingPoints);
}

bool Car::isDead() {
    return health.isDead();
}

Car::~Car() {

}
