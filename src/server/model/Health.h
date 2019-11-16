#ifndef MICROMACHINES_HEALTH_H
#define MICROMACHINES_HEALTH_H

class Health {
private:
    int actualHealth;
    int maximumHealth;
public:
    explicit Health();
    void receiveDamage(int damage);
    void receiveHealing(int healingPoints);
    int getHealth();
    bool isDead();
};

#endif //MICROMACHINES_HEALTH_H
