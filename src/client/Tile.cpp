#include "Tile.h"

Tile::Tile(Window& window,
           const std::string& img,
           int x, int y, int h, int w) :
           texture(window.createTextureFrom(img)),
           box{x, y, w, h} { }

Tile::Tile(Tile&& other) :
    texture(other.texture) {
    this->box = other.box;
}

void Tile::render(Camera& cam){
    SDL_Rect box2;

    box2.x = box.x - cam.x;
    box2.y = box.y - cam.y;
    box2.h = box.h ;
    box2.w = box.w ;

    if ((box2.x + box2.w) > 0 && (box2.y + box2.h) > 0
        && (box2.x < 1200) && (box2.y < 700))
        this->texture.render( box2, 0);
}