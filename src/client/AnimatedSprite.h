#ifndef MICROMACHINES_ANIMATEDSPRITE_H
#define MICROMACHINES_ANIMATEDSPRITE_H

#include "Texture.h"
#include "Camera.h"
#include "TextureRepository.h"
#include "Sprite.h"
#include <vector>

class AnimatedSprite: public Sprite{
private:
    std::vector<SDL_Rect> frames;

public:
    AnimatedSprite(Window &main,
                   const std::string &file,
                   int frames,
                   int frame_h,
                   int frame_w,
                   int h,
                   int w);

    void render(int x, int y, int angle, Camera& cam);

};

#endif
