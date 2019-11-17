#include "TileMap.h"
#include "Window.h"
#include "Constants.h"
#include "Car.h"
#include <nlohmann/json.hpp>
#include <Identifiers.h>

TileMap::TileMap(Window& window, const nlohmann::json& map) :
window(window) {;
    this->numbers = map["tiles"].get<std::vector<std::vector<int>>>();
    int sized = map["tiles"].size();
    int x, y = - (sized - 1) * TILE_HEIGHT * MtoP / 2;

    for (auto& tileList : map["tiles"]) {
        std::vector<int> tiles2 = tileList.get<std::vector<int>>();
        int size2 = tiles2.size();
        x = - (size2 - 1) * TILE_WIDTH * MtoP / 2;
        for (int j : tiles2) {
            this->tiles.emplace_back(std::move(Tile(window, TILE_0, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            if (j == THIRD_QUAD_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_1, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == SECOND_QUAD_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_2, x, y, TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == FOURTH_QUAD_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_3, x, y, TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == FIRST_QUAD_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_4, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == LEFT_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_5, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == RIGHT_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_6, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == UP_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_7, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == DOWN_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_8, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            x += (MtoP * TILE_WIDTH);
        }
        y += (MtoP * TILE_HEIGHT);
    }
}


void TileMap::render(Camera& cam ){
    for (Tile &tile : this->tiles)
        tile.render(cam);
}

std::vector<std::vector<int>>& TileMap::getTileNumbers() {
    return this->numbers;
}

TileMap::~TileMap() { }
