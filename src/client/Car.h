#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include "Entity.h"
#include "BaseSprite.h"
#include "Window.h"
#include "Camera.h"

#define CAR_H 15
#define CAR_W 6

class Car: public Entity{
private:
    BaseSprite sprite;
    int health;
    int x;
    int y;
    int angle;

public:
    Car(const std::string& file, Window& win);
    void setPos(int x, int y, int angle);
    int getXPos();
    int getYPos();
    void render(Camera& cam);
    ~Car();
};


#endif
