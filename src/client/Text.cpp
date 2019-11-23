#include "Text.h"
#include <SDL2/SDL_ttf.h>

Text::Text(Window &w, const std::string &font_path, int size) :
w(w),
text("ahre"){
    this->font = TTF_OpenFont(font_path.c_str(), size);
    actualColor = {255, 255, 255};
    SDL_Surface* msg = TTF_RenderText_Blended_Wrapped(font, text.c_str(), actualColor, w.getWidth());
    int width, height;
    TTF_SizeText(font, text.c_str(), &width, &height);
    this->texture = SDL_CreateTextureFromSurface(w.getRenderer(), msg);
    SDL_FreeSurface(msg);
}

void Text::render(SDL_Rect r) {
    SDL_Surface* msg = TTF_RenderText_Blended_Wrapped(font, text.c_str(), actualColor, w.getWidth());
    this->texture = SDL_CreateTextureFromSurface(w.getRenderer(), msg);
    Texture t(this->texture, w);
    t.render(r, 0);
}

void Text::setColor(SDL_Color& c){
    this->actualColor = c;
}

void Text::setText(std::string &text) {
    this->text = text;
}

Text::~Text() {
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

