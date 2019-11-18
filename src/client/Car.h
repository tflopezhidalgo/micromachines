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
    int x;
    int y;
    int angle;
    bool blinded;

public:
    Car(const std::string& file, Window& win);
    void setState(int x, int y, int angle, int health, bool blinded);
    int getAngle();
    int getXPos();
    int getYPos();
    void render(Camera& cam);
    bool isBlinded();
    ~Car();
};


#endif
