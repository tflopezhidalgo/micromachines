#include "Tile.h"

Tile::Tile(Window& window,
           const std::string& img,
           int x, int y, int h, int w) :
           texture(window.createTextureFrom(img), window),
           box{x, y, w, h} { }

void Tile::render(){
    this->texture.render(box);
}