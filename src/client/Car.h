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
    void setPos(int x, int y, int angle);
    int getXPos() override {
        return sprite.getXPos();
    }

    int getYPos() override {
        return sprite.getYPos();
    }
    void render();
    ~Car() {

    }
};


#endif
