//
// Created by eliana on 5/11/19.
//
#include <iostream>
#include "Converter.h"

std::tuple<int, int> Converter::getLuaMapPosition(int pos_x, int pos_y, int matrixHeight, int matrixWidth) {
    std::cout << "x:" <<pos_x << " y:" << pos_y << " - ";
    int widthMap = matrixWidth * TILE_WIDTH;
    int heightMap = matrixHeight * TILE_HEIGHT;

    int refCenterX = widthMap / 2;
    int refCenterY = heightMap / 2;

    float realPosX = (refCenterX + pos_x);
    float realPosY = (refCenterY + pos_y);

    int luaPosX = abs(round((double)realPosX /1000*3)) + 1;
    int luaPosY = abs(round((double)realPosY /1000 *3*3)) + 1;

    return std::make_tuple(luaPosX, luaPosY);
}
