#ifndef MICROMACHINES_ANIMATION_H
#define MICROMACHINES_ANIMATION_H

#include "Texture.h"
#include "Camera.h"
#include "TextureRepository.h"
#include <vector>

class Animation: public Entity {
private:
    std::vector<Texture> frames;

public:
    Animation(Window& window, const std::string& file, int frames, int x, int y, int h, int w){
        y = 0;
        x = 0;
        for (int i = 0; i < frames; i++) {
            SDL_Rect rect = {x, y, h, w};
            Texture f(std::move(TextureRepository::getTexture(file, window)));
            f.setRect(rect);
            this->frames.push_back(std::move(f));
            rect.x += w;
        }
    }

    void render(Camera& cam){
        static int counter;
        if (counter == 5)
            counter = 0;
        SDL_Rect r = {0,0, 100, 100};
        frames[counter].render(r, 0);
    }


};

#endif
