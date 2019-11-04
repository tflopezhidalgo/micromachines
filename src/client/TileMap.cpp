#include <sys/param.h>
#include "TileMap.h"
#include "Window.h"
#include "../common/Macros.h"
#include "Car.h"
#include <nlohmann/json.hpp>

TileMap::TileMap(Window& window, const std::string& mapFile, int zoom, int offset) :
window(window) {
    std::ifstream in(mapFile);
    nlohmann::json json_p;
    in >> json_p;
    int sized = json_p["tiles"].size();
    int x, y = - (sized - 1) * TILE_HEIGHT * zoom / 2;

    for (auto& tileList : json_p["tiles"]) {
        std::vector<int> tiles2 = tileList.get<std::vector<int>>();
        int size2 = tiles2.size();
        x = - (size2 - 1) * TILE_WIDTH * zoom / 2;
        for (int j : tiles2) {
            this->tiles.emplace_back(std::move(Tile(window, GRASS_TILE, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            if (j == 1) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_1, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == 2) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_2, x, y, TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == 3) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_3, x, y, TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == 4) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_4, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == 5) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_5, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == 6) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_6, x, y,  TILE_HEIGHT, TILE_WIDTH)));
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
