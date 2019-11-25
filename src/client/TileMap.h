#ifndef MICROMACHINES_TILEMAP_H
#define MICROMACHINES_TILEMAP_H

#include "Tile.h"
#include "Object.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <json.hpp>

#define TILE_0 "../media/tiles/00_Road.png"
#define TILE_1 "../media/tiles/01_Road.png"
#define TILE_2 "../media/tiles/02_Road.png"
#define TILE_3 "../media/tiles/03_Road.png"
#define TILE_4 "../media/tiles/04_Road.png"
#define TILE_5 "../media/tiles/05_Road.png"
#define TILE_6 "../media/tiles/06_Road.png"
#define TILE_7 "../media/tiles/07_Road.png"
#define TILE_8 "../media/tiles/08_Road.png"
#define TILE_9 "../media/tiles/09_Road.png"
#define TILE_10 "../media/tiles/10_Road.png"
#define TILE_11 "../media/tiles/11_Road.png"
#define TILE_12 "../media/tiles/12_Road.png"
#define TILE_13 "../media/tiles/13_Road.png"
#define TILE_14 "../media/tiles/14_Road.png"

class TileMap {
    private:
        std::vector<Tile> tiles;
        Window& window;
        std::vector<std::vector<int>> numbers;

    public:
        TileMap(Window& window, const nlohmann::json& map);
        void render(Camera& cam);
        std::vector<std::vector<int>>& getTileNumbers();
        ~TileMap();
};

#endif
