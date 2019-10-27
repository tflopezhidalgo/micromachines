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

void Tile::render(){
    this->texture.render(box, 0);
}