//
// Created by eliana on 5/11/19.
//
#include <iostream>
#include "Converter.h"

std::tuple<int, int> Converter::getLuaMapPosition(int pos_x, int pos_y, int matrixHeight, int matrixWidth) {
    std::cout << "x:" <<pos_x << " y:" << pos_y << " - ";
    int widthMap = (matrixWidth - 1) * TILE_WIDTH * MtoP / 2;
    int heightMap = (matrixHeight - 1) * TILE_HEIGHT * MtoP / 2;

    std::cout << "w:" << widthMap << "- h:" << heightMap << "\n";
    int refCenterX = widthMap / 2;
    int refCenterY = heightMap / 2;

    std::cout << "center(" << refCenterX << ", " << refCenterY << ")\n";
    float realPosX = (refCenterX + pos_x);
    float realPosY = (refCenterY + pos_y);

    std::cout << "realpos(" << realPosX << ", " << realPosY << ")\n";
    //int luaPosX = abs(round((double)realPosX /1000*3)) + 1;
    int luaPosX = abs(round((double)realPosX));
    //int luaPosY = abs(round((double)realPosY /1000 *3*3)) + 1;


    int luaPosY = abs(round((double)realPosY));
    std::cout << "luapos(" << luaPosX << ", " << luaPosY << ")\n";
    return std::make_tuple(luaPosX, luaPosY);
}
