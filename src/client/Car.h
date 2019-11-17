#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include "Entity.h"
#include "Sprite.h"
#include "Window.h"
#include "Camera.h"
#include "Health.h"
#include "AnimatedSprite.h"
#include "Identifiers.h"

class Car: public Entity{
private:
    Sprite sprite;
    AnimatedSprite animation;
    Health health;
    bool exploding;
    int x;
    int y;
    int angle;

public:
    Car(const std::string& file, Window& win);
    void setState(int x, int y, int angle, int health, bool exploding);
    int getAngle();
    int getXPos();
    int getYPos();
    void render(Camera& cam);
    ~Car();
};


#endif
