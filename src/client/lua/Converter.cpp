//
// Created by eliana on 5/11/19.
//

#include "Converter.h"

std::tuple<int, int> Converter::getLuaMapPosition(int pos_x, int pos_y, int matrixHeight, int matrixWidth) {
    int widthMap = matrixWidth * 15;//TILE_WIDTH;
    int heightMap = matrixHeight * 11;//TILE_HEIGHT;

    int refCenterX = widthMap / 2;
    int refCenterY = heightMap / 2;

    int realPosX = refCenterX + pos_x;
    int realPosY = refCenterY + pos_y;

    int luaPosX = realPosX / matrixWidth;
    int luaPosY = realPosY / matrixHeight;
    return std::make_tuple(luaPosX, luaPosY);
}
