#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include "Entity.h"
#include "BaseSprite.h"
#include "Window.h"

class Car: public Entity{
private:
    BaseSprite sprite;
    int health;
    int x;
    int y;

public:
    Car(const std::string& file, int h, int w, Window& win);
    void setPos(int x, int y);
    int getXPos() override {
        return x;
    }

    int getYPos() override {
        return y;
    }
    void render();
    ~Car() {

    }
};


#endif
