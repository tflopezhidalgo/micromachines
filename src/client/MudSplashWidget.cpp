#include "MudSplashWidget.h"

#define MUD_SPRITE "../media/sprites/mud_screen_sprite.png" 

MudSplashWidget::MudSplashWidget(Window& window):
main(window),
texture(std::move(window.createTextureFrom(MUD_SPRITE))),
splash_sound("../media/sounds/mud_splash.wav"),
played_sound(false){
    this->target = NULL;
}

void MudSplashWidget::onAdded(Car* car){
    this->target = car;
}

void MudSplashWidget::onRender(){
    if (this->target == NULL)
        return;
    
    if (target->isBlinded()){
        SDL_Rect r = {0, 0, main.getWidth(), main.getHeight()};
        this->texture.render(r, 0);
        if (!played_sound) {
            this->splash_sound.play();
            played_sound = true;
        }
    } else
        played_sound = false;


}


