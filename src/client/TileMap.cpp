#include "TileMap.h"
#include "Window.h"

TileMap::TileMap(Window& window, const std::string& mapFile)
    : window(window) {
    int x = 0, y = 0;
    std::fstream in(mapFile);
    for (int i = 0; i < 16; ++i) {
        x = 0;
        for (int j = 0; j < 15; ++j) {
            int type = -1;
            in >> type;
            this->tiles.emplace_back(std::move(Tile(window, GRASS_TILE, x, y, TILE_HEIGHT, TILE_WIDTH)));
            if (type == 1) {
                tiles.emplace_back(std::move(Tile(window, TILE_1, x, y, TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (type == 2) {
                tiles.emplace_back(std::move(Tile(window, TILE_2, x, y, TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (type == 3) {
                tiles.emplace_back(std::move(Tile(window, TILE_3, x, y, TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (type == 4) {
                tiles.emplace_back(std::move(Tile(window, TILE_4, x, y, TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (type == 5) {
                tiles.emplace_back(std::move(Tile(window, TILE_5, x, y, TILE_HEIGHT, TILE_WIDTH)));
            }
            x += TILE_WIDTH;
        }
        y += TILE_HEIGHT;
    }
    in.close();
}


void TileMap::render(){
    for (Tile &tile : this->tiles)
        tile.render();
}

TileMap::~TileMap() { }