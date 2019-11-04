#ifndef MICROMACHINES_CAMERA_H
#define MICROMACHINES_CAMERA_H

#include "Window.h"
#include "Entity.h"

class Camera {
private:
    Entity* target;
    Window& window;
    SDL_Rect cameraInfo;
    int zoom;

public:
    Camera(Window& w);
    void setOnTarget(Entity* e);
    SDL_Rect translate(SDL_Rect& origin);
    bool collideWith(SDL_Rect& obj_dimensions);
    void update();
    int getZoom();
    bool targetSet();

};
#endif
