#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include "Entity.h"
#include "BaseSprite.h"
#include "Window.h"
#include "Camera.h"
#include "Health.h"

class Car: public Entity{
private:
    BaseSprite sprite;
    Health health;
    int x;
    int y;
    int angle;

public:
    Car(const std::string& file, Window& win);
    void setState(int x, int y, int angle, int health);
    int getAngle();
    int getXPos();
    int getYPos();
    void render(Camera& cam);
    ~Car();
};


#endif
