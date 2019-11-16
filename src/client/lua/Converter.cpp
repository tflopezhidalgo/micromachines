#include "Converter.h"
#include <iostream>

std::tuple<int, int> Converter::getLuaMapPosition(int pos_x, int pos_y, int matrixHeight, int matrixWidth) {
    //std::cout << "x:" <<pos_x << " y:" << pos_y << " - ";
    int widthMap = matrixWidth * TILE_WIDTH;
    int heightMap = matrixHeight * TILE_HEIGHT;

    int centerX = widthMap / 2;
    int centerY = heightMap / 2;

    int posRefX = (pos_x * 1000 / MtoP) / 1000;
    int posRefY = (pos_y * 1000 / MtoP) / 1000;

    int realPosX = posRefX + centerX;
    int realPosY = posRefY + centerY;

    //std::cout << "realpos(" << realPosX << ", " << realPosY << ")\n";
    int luaPosX = abs(round((double)realPosX / TILE_WIDTH));
    int luaPosY = abs(round((double)realPosY / TILE_HEIGHT));

    return std::make_tuple(luaPosX, luaPosY);
}
