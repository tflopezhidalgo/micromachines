#ifndef MICROMACHINES_CAMERA_H
#define MICROMACHINES_CAMERA_H

#include "Window.h"
#include "Entity.h"

class Camera {
private:
    Entity* e;
    Window& window;
    SDL_Rect cameraInfo;

public:
    int x;
    int y;
    int h;
    int w;
    int zoom;
    Camera(Window& w);
    void setOnTarget(Entity* e);
    SDL_Rect translate(SDL_Rect& origin);
    void update();
    int getZoom();
    bool targetSet();

};
#endif
