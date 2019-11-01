#include "Camera.h"
#include "Entity.h"
#include "Window.h"

#define MtoP 6      // Relación metros a píxeles

Camera::Camera(Window& w) :
window(w) {
    this->cameraInfo = {0, 0, 0, 0};
    e = NULL;
}

void Camera::setOnTarget(Entity* e) {
    this->e = e;
}

SDL_Rect Camera::translate(SDL_Rect &origin) {
    SDL_Rect translated = {origin.x - x,
                           origin.y - y,
                           origin.w * zoom,0};
    return translated;
}

void Camera::update() {
    if (e == NULL)
        return;

    this->x = e->getXPos() - w / 2;
    this->y = e->getYPos() - h / 2;
    this->h = window.getHeight();
    this->w = window.getWidth();
    this->zoom = MtoP;
}

int Camera::getZoom() {
    return zoom;
}

bool Camera::targetSet() {
    return (e != NULL);
}
