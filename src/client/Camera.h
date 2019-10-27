#ifndef MICROMACHINES_CAMERA_H
#define MICROMACHINES_CAMERA_H

#include "BaseSprite.h"
#include "Window.h"
#include "Entity.h"

static const int CAMERA_SCALE = 0;  /*  Ojo que afecta como se
                                     *  unen los tiles :(
                                     */


class Camera: public Entity {
    private:
        Window& mainW;
        Entity& e;

    public:
        Camera(Window& new_w, Entity& e) :
            mainW(new_w), e(e){
        }

        void render(){
            int h = mainW.getHeight();
            int w = mainW.getWidth();
            mainW.setCamera(
                    e.getXPos() - w / 2,
                    e.getYPos() - h / 2,
                    CAMERA_SCALE);
        }

};


#endif
