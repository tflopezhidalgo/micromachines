#ifndef MICROMACHINES_THROWABLE_H
#define MICROMACHINES_THROWABLE_H

#include "Object.h"
#include "Sprite.h"
#include "Identifiers.h"

class Throwable : public Object {
private:
    EntityStatus state;
    Sprite sprite;
    Sprite onFlySprite;
    int x;
    int y;

public:
    Throwable(Sprite sprite, Sprite onFlySprite, EntityStatus state, int x, int y);
    Throwable(Throwable&& other);
    void setPosition(int x, int y) override;
    int getXPos() override;
    int getYPos() override;
    void setState(EntityStatus state) override;
    void render(Camera& cam) override;


};

#endif
