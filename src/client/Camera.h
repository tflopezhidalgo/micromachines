#ifndef MICROMACHINES_CAMERA_H
#define MICROMACHINES_CAMERA_H

#include "BaseSprite.h"
#include "Window.h"

static const int CAMERA_SCALE = 0;  /*  Ojo que afecta como se
                                     *  unen los tiles :(
                                     */


class Camera {
    private:
        Window& mainW;
        BaseSprite& e;

    public:
        Camera(Window& new_w, BaseSprite& e) :
            mainW(new_w), e(e){
        }

        void update(){
            int h = mainW.getHeight();
            int w = mainW.getWidth();
            mainW.setCamera(
                    e.getXPos() - w / 2,
                    e.getYPos() - h / 2,
                    CAMERA_SCALE);
        }

};


#endif
