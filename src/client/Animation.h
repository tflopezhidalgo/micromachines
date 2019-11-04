#ifndef MICROMACHINES_ANIMATION_H
#define MICROMACHINES_ANIMATION_H

#include "Texture.h"
#include "Camera.h"
#include "TextureRepository.h"
#include <vector>

class Animation: public Entity {
private:
    std::vector<SDL_Rect> frames;
    Texture texture;

public:
    Animation(Window& window, const std::string& file, int frames, int x, int y, int h, int w)
    : texture(std::move(TextureRepository::getTexture(file, window))) {
        y = 0;
        x = 0;
        SDL_Rect rect = {x, y, h, w};
        for (int i = 0; i < frames; i++) {
            this->frames.push_back(rect);
            rect.x += w;
        }
    }

    void render(Camera& cam){
        static float counter;
        if (counter > 5)
            counter = 0;
        SDL_Rect r = {0,0, 200, 200};
        texture.setRect(frames[counter]);
        texture.render(r, 0);
        counter = counter + 0.20;
        std::cout << "Counter vale " << counter << std::endl;
    }


};

#endif
