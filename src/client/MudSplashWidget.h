#ifndef _MUD_SPLASH_WID_
#define _MUD_SPLASH_WID_

#include "CameraWidget.h"
#include "Window.h"
#include "Car.h"

class MudSplashWidget : public CameraWidget {
private:
    Car* target;
    Texture texture;   
    Window& main; 
    Sound splash_sound;
    bool played_sound;

public:
    explicit  MudSplashWidget(Window& window);
    void onRender() override;
    void onAdded(Car* target) override;
};


#endif
