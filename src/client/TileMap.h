#ifndef MICROMACHINES_TILEMAP_H
#define MICROMACHINES_TILEMAP_H

#include "Tile.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

//TODO: Falta pista recta en | |

#define TILE_1 "../media/tiles/01_Road.png"
#define TILE_2 "../media/tiles/02_Road.png"
#define TILE_3 "../media/tiles/03_Road.png"
#define TILE_4 "../media/tiles/04_Road.png"
#define TILE_5 "../media/tiles/05_Road.png"
#define TILE_6 "../media/tiles/06_Road.img"
#define GRASS_TILE "../media/tiles/Grass_Tile.png"

// De qué forma queremos que la muestre
#define TILE_HEIGHT 1200
#define TILE_WIDTH 1200

class TileMap {
    private:
        std::vector<Tile*> tiles;
        Window& window;

    public:
        TileMap(Window& window, const std::string& mapFile) :
            window(window) {
            int x = 0, y = 0;
            std::fstream in(mapFile);
            for (int i = 0; i < 2; ++i) {
                x = 0;
                for (int j = 0; j < 10; ++j) {
                    int type = -1;
                    in >> type;
                    this->tiles.push_back(new Tile(window, GRASS_TILE, x, y, TILE_HEIGHT, TILE_WIDTH));
                    if (type == 1)
                        this->tiles.push_back(new Tile(window, TILE_1, x, y, TILE_HEIGHT, TILE_WIDTH));
                    else if (type == 2)
                        this->tiles.push_back(new Tile(window, TILE_2, x, y, TILE_HEIGHT, TILE_WIDTH));
                    else if (type == 3)
                        this->tiles.push_back(new Tile(window, TILE_3, x, y, TILE_HEIGHT, TILE_WIDTH));
                    else if (type == 4)
                        this->tiles.push_back(new Tile(window, TILE_4, x, y, TILE_HEIGHT, TILE_WIDTH));
                    else if (type == 5)
                        this->tiles.push_back(new Tile(window, TILE_5, x, y, TILE_HEIGHT, TILE_WIDTH));
                    x += TILE_WIDTH;
                }
                y += TILE_HEIGHT;
            }
            in.close();
        }

        void render(){
            for (Tile* tile : tiles)
                tile->render();
        }

        ~TileMap(){
            for (Tile* tile : tiles)
                delete tile;
        }
};

#endif
