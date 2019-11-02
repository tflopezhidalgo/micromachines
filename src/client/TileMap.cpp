#include "TileMap.h"
#include "Window.h"

// Ojo que offset está deprecado

TileMap::TileMap(Window& window, const std::string& mapFile, int zoom, int offset) :
window(window) {
    // Harcodeado, en proceso de desharcodeo jeje
    float x, y = -7.5 * zoom * TILE_HEIGHT;
    y = -242 * zoom;
    std::fstream in(mapFile);
    for (int i = 0; i < 15; i++) {
        x = - 7.5 * zoom * TILE_WIDTH;
        x = - 245.5 * zoom;
        for (int j = 0; j < 15; j++) {
            int type = -1;
            in >> type;
            this->tiles.emplace_back(std::move(Tile(window, GRASS_TILE, x, y, zoom * TILE_HEIGHT, zoom*TILE_WIDTH)));
            if (type == 1) {
                tiles.emplace_back(std::move(Tile(window, TILE_1, x, y, zoom * TILE_HEIGHT, zoom*TILE_WIDTH)));
            }
            else if (type == 2) {
                tiles.emplace_back(std::move(Tile(window, TILE_2, x, y, zoom * TILE_HEIGHT, zoom*TILE_WIDTH)));
            }
            else if (type == 3) {
                tiles.emplace_back(std::move(Tile(window, TILE_3, x, y, zoom * TILE_HEIGHT, zoom*TILE_WIDTH)));
            }
            else if (type == 4) {
                tiles.emplace_back(std::move(Tile(window, TILE_4, x, y, zoom * TILE_HEIGHT, zoom*TILE_WIDTH)));
            }
            else if (type == 5) {
                tiles.emplace_back(std::move(Tile(window, TILE_5, x, y, zoom * TILE_HEIGHT, zoom*TILE_WIDTH)));
            }
            x += (zoom * TILE_WIDTH);
        }
        y += (zoom*TILE_HEIGHT);
    }
    in.close();
}


void TileMap::render(Camera& cam ){
    for (Tile &tile : this->tiles)
        tile.render(cam);
}

TileMap::~TileMap() { }
