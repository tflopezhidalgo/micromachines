#include "Camera.h"
#include "Object.h"
#include "Window.h"
#include "../common/Constants.h"
#include "Car.h"
#include "Text.h"
#include <SDL2/SDL_ttf.h>

Camera::Camera(Window& w, Texture& texture) :
    window(w),
    texture(texture) {
    this->cameraInfo = {0, 0, 0, 0};
    target = NULL;
	this->zoom = MtoP;
}

void Camera::addWidget(CameraWidget* widget) {
    this->widgets.push_back(widget);
}

void Camera::setOnTarget(Car* e) {
    this->target = e;
}

SDL_Rect Camera::translate(SDL_Rect &origin) {
    SDL_Rect translated = {origin.x - cameraInfo.x - (origin.w / 2) * zoom,
                           origin.y - cameraInfo.y - (origin.h / 2) * zoom,
                           origin.w * zoom,
                           origin.h * zoom};
    return translated;
}

bool Camera::collideWith(SDL_Rect& obj_dimensions) {

    if ((obj_dimensions.x + obj_dimensions.w) < 0 ||
            (obj_dimensions.y + obj_dimensions.h) < 0)
        return false;

    if (obj_dimensions.x > cameraInfo.w ||
        obj_dimensions.y  > cameraInfo.h)
        return false;

    return true;
}

void Camera::update() {
    if (target == NULL)
        return;

    this->cameraInfo.x = target->getXPos() - (cameraInfo.w / 2);
    this->cameraInfo.y = target->getYPos() - (cameraInfo.h / 2);
    this->cameraInfo.h = window.getHeight();
    this->cameraInfo.w = window.getWidth();
    this->zoom = MtoP;
}

void Camera::render() {

    std::string path("../media/fonts/myFont.TTF");
    std::string text_msg(std::to_string(target->getLapsDone()));

    Text text(this->window, path, 80);
    text.setText(text_msg);
    SDL_Color color = {230, 210, 20};
    text.setColor(color);
    SDL_Rect r = {window.getWidth() - 100, window.getHeight() - 150, 100, 150};
    text.render(r);

    if (target->isBlinded()) {
        SDL_Rect r = {0, 0, window.getWidth(), window.getHeight()};
        this->texture.render(r, 0);
    }

    for (CameraWidget* widget: widgets)
        widget->OnRender();
}

int Camera::getZoom() {
    return zoom;
}

bool Camera::targetSet() {
    return (target != NULL);
}
