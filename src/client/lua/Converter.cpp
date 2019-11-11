//
// Created by eliana on 5/11/19.
//
#include <iostream>
#include "Converter.h"

std::tuple<int, int> Converter::getLuaMapPosition(int pos_x, int pos_y, int matrixHeight, int matrixWidth) {
    std::cout << "x:" <<pos_x << " y:" << pos_y << " H:" << matrixHeight <<" w:" << matrixWidth << std::endl;
    int widthMap = matrixWidth * TILE_WIDTH;
    int heightMap = matrixHeight * TILE_HEIGHT;

    int refCenterX = widthMap / 2;
    int refCenterY = heightMap / 2;

    double realPosX = refCenterX + (pos_x / 1000);
    double realPosY = refCenterY + (pos_y / 1000);

    std::cout << "a" << realPosX / (matrixWidth) << std::endl;
    std::cout << "b" << realPosX / (matrixWidth+TILE_WIDTH) << std::endl;
    std::cout << "c" << realPosX / (TILE_WIDTH) << std::endl;
    double luaPosX = round(realPosX / (matrixWidth+TILE_WIDTH)) + 1;
    double luaPosY = round(realPosY / (matrixHeight+TILE_HEIGHT)) + 1;

    std::cout << luaPosX << " " <<luaPosY;
    return std::make_tuple((int)luaPosX, (int)luaPosY);
}
