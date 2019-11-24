#include "Text.h"
#include <SDL2/SDL_ttf.h>

Text::Text(Window &w, const std::string &font_path, int size) :
w(w),
text_texture(NULL, w) {

    this->font = TTF_OpenFont(font_path.c_str(), size);
    this->actualColor = {255, 255, 255};
    SDL_Surface* msg = TTF_RenderText_Blended_Wrapped(font, text.c_str(), actualColor, w.getWidth());
    int width, height;
    TTF_SizeText(font, text.c_str(), &width, &height);
    SDL_Texture* aux_txt = SDL_CreateTextureFromSurface(w.getRenderer(), msg);
    SDL_FreeSurface(msg);
    this->text_texture = std::move(Texture(aux_txt, w)); // Se borra en el destructor de Textura

}

Text::Text(Text&& other) :
w(other.w),
text_texture(std::move(other.text_texture)),
actualColor(other.actualColor),
text(other.text),
position(other.position){
    font = other.font;
    other.font = NULL; }


void Text::render() {
    text_texture.render(this->position, 0);
}

void Text::setColor(SDL_Color& c){
    this->actualColor = c;
    SDL_Surface* msg = TTF_RenderText_Blended_Wrapped(font, text.c_str(), actualColor, w.getWidth());
    SDL_Texture* aux = SDL_CreateTextureFromSurface(w.getRenderer(), msg);
    this->text_texture = std::move(Texture(aux, w));
    SDL_FreeSurface(msg);
}

void Text::setText(const std::string &text) {
    this->text = std::move(text);
    SDL_Surface* msg = TTF_RenderText_Blended_Wrapped(font, this->text.c_str(), actualColor, w.getWidth());
    SDL_Texture* text_aux = SDL_CreateTextureFromSurface(w.getRenderer(), msg);
    this->text_texture = std::move(Texture(text_aux, w));
    SDL_FreeSurface(msg);
}

void Text::setPositionAndSize(SDL_Rect& r) {
    this->position = r;
}

Text::~Text() { }

