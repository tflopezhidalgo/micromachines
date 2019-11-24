#ifndef MICROMACHINES_TEXT_H
#define MICROMACHINES_TEXT_H

#include "Window.h"
#include "Texture.h"
#include <SDL2/SDL_ttf.h>

class Text {
private:
    Window& w;
    Texture text_texture;
    TTF_Font* font;
    SDL_Color actualColor;
    std::string text;
    SDL_Rect position;

public:
    Text(Window& w, const std::string &font_path, int size);

    Text(Text&& other);

    void render();

    void setColor(SDL_Color& c);

    void setText(const std::string &text);

    void setPositionAndSize(SDL_Rect& r);

    ~Text();
};

#endif
