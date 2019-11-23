#include <unistd.h>
#include "AnimatedSprite.h"
#include "Sprite.h"

AnimatedSprite::AnimatedSprite(Window &main,
                               const std::string &path,
                               int frames,
                               int frame_h,
                               int frame_w,
                               int h,
                               int w)
    : Sprite(main, path, h, w) {
    SDL_Rect rect = {0, 0, frame_h, frame_w};
    for (int i = 0; i < frames; i++) {
        this->frames.push_back(rect);
        rect.x += frame_w;
    }
}

void AnimatedSprite::render(int x, int y, int angle, Camera& cam) {
    static float counter;
    if (int(counter) > frames.size())
        counter = 0;
    SDL_Rect r = {x, y, h, w}; // Donde se renderiza
    r = cam.translate(r);
    texture.setRect(frames[counter]);
    texture.render(r, angle);
    counter = counter + 0.065;
}


