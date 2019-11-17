#ifndef MICROMACHINES_HEALTH_H
#define MICROMACHINES_HEALTH_H

#include <SDL2/SDL_image.h>
#include "Window.h"
#include "Camera.h"

class Health {
private:
    int actualHealth;
    SDL_Rect healthBar;
    Window& w;

public:
    Health(Window& w);

    void setActualHealth(int actualHealth);

    void renderAt(int x, int y, Camera& cam);

    int getHealth();
};

#endif
