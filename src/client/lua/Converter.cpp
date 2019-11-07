//
// Created by eliana on 5/11/19.
//

#include "Converter.h"

std::tuple<int, int> Converter::getLuaMapPosition(int pos_x, int pos_y, int matrixHeight, int matrixWidth) {
    int widthMap = matrixWidth * TILE_WIDTH;
    int heightMap = matrixHeight * TILE_HEIGHT;

    double refCenterX = widthMap / 2;
    double refCenterY = heightMap / 2;

    double realPosX = refCenterX + pos_x;
    double realPosY = refCenterY + pos_y;

    double luaPosX = round(realPosX / (matrixWidth+TILE_WIDTH)) + 1;
    double luaPosY = round(realPosY / (matrixHeight+TILE_HEIGHT)) + 1;

    return std::make_tuple((int)luaPosX, (int)luaPosY);
}
