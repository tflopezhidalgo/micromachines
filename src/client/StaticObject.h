#ifndef MICROMACHINES_STATICOBJECT_H
#define MICROMACHINES_STATICOBJECT_H

#include "Object.h"
#include "Sprite.h"

class StaticObject : public Object {
private:
    int x;
    int y;
    Sprite sprite;

public:
    explicit StaticObject(Sprite sprite);
    void setPosition(int x, int y) override;
    void render(Camera& camera) override;
    void setState(EntityStatus state) override;
    int getXPos() override;
    int getYPos() override;
};


#endif
