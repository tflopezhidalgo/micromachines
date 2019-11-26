#ifndef MICROMACHINES_CAMERA_H
#define MICROMACHINES_CAMERA_H

#include <vector>
#include "Window.h"
#include "Object.h"
#include "Texture.h"
#include "CameraWidget.h"
#include "Text.h"

class Car;

class Camera {
private:
    Car* target;
    Window& window;
    SDL_Rect cameraInfo;
    int zoom;
    Text text;
    Text velocimeter;
    std::vector<CameraWidget*> widgets;

public:
    explicit Camera(Window& w);
    void addWidget(CameraWidget* widget);
    void setOnTarget(Car* e);
    SDL_Rect translate(SDL_Rect& origin);
    bool collideWith(SDL_Rect& obj_dimensions);
    void update();
    void render();
    int getZoom();

};
#endif
