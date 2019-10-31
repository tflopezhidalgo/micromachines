#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include "Entity.h"
#include "BaseSprite.h"
#include "Window.h"
#include "Camera.h"

class Car: public Entity{
private:
    BaseSprite sprite;
    int health;
    int x;
    int y;
    int angle;

public:
    Car(const std::string& file, int h, int w, Window& win);
    void setPos(int x, int y, int angle);
    int getXPos();
    int getYPos();
    void render(Camera& cam);
    ~Car();
};


#endif
