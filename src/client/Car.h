#ifndef MICROMACHINES_CAR_H
#define MICROMACHINES_CAR_H

#include "Object.h"
#include "Sprite.h"
#include "Window.h"
#include "Camera.h"
#include "Health.h"
#include "Sound.h"
#include "AnimatedSprite.h"
#include "Identifiers.h"
#include <SDL2/SDL_mixer.h>

class Car {
private:
    Sprite sprite;
    AnimatedSprite animation;
    Health health;
    Sound crashSound;
    int x;
    int y;
    int angle;
    int lapsDone;
    bool blinded;

public:
    Car(const std::string& file, Window& win);
    void setState(int x, int y, int angle, int health, int lapsDone, bool blinded);
    int getAngle();
    int getXPos();
    int getYPos();
    bool isBlinded();
    int getLapsDone();
    void render(Camera& cam);
    ~Car();
};


#endif
