#ifndef MICROMACHINES_TEXT_H
#define MICROMACHINES_TEXT_H

#include "Window.h"
#include "Texture.h"
#include <SDL2/SDL_ttf.h>

class Text {
private:
    Window& w;
    SDL_Texture* texture;
    TTF_Font* font;
    SDL_Color actualColor;
    std::string text;

public:
    Text(Window& w, std::string &font_path, int size);

    void render(SDL_Rect r);

    void setColor(SDL_Color& c);

    void setText(std::string &text);

    ~Text();
};

#endif
