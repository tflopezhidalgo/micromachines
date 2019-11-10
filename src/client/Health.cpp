#include "Health.h"
#include "Window.h"

#define HEALTH_BAR_H 1
#define HEALTH_BAR_W 10

Health::Health(Window &w) :
healthBar{0, 0, HEALTH_BAR_W, HEALTH_BAR_H},
w(w),
actualHealth(0)
{}

void Health::setActualHealth(int actualHealth) {
    this->actualHealth = actualHealth;
}

void Health::renderAt(int x, int y, Camera& cam) {
    this->healthBar.x = x;
    this->healthBar.y = y;
    this->healthBar.w = HEALTH_BAR_W * actualHealth / 100;
    SDL_Rect translatedHealthBar = cam.translate(healthBar);
    translatedHealthBar.y -= 70;
    SDL_SetRenderDrawColor(this->w.getRenderer(), 0, 255, 0, 0);
    SDL_RenderFillRect(this->w.getRenderer(), &translatedHealthBar);
    SDL_SetRenderDrawColor(this->w.getRenderer(), 0, 0, 0, 0);
}
