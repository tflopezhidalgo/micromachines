#ifndef MICROMACHINES_CAMERA_H
#define MICROMACHINES_CAMERA_H

#include <vector>
#include "Window.h"
#include "Object.h"
#include "Texture.h"
#include "CameraWidget.h"

class Car;

class Camera {
private:
    Car* target;
    Window& window;
    Texture& texture;
    SDL_Rect cameraInfo;
    int zoom;
    std::vector<CameraWidget*> widgets;

public:
    Camera(Window& w, Texture& texture);
    void addWidget(CameraWidget* widget);
    void setOnTarget(Car* e);
    SDL_Rect translate(SDL_Rect& origin);
    bool collideWith(SDL_Rect& obj_dimensions);
    void update();
    void render();
    int getZoom();
    bool targetSet();

};
#endif
