#ifndef MICROMACHINES_CONVERTER_H
#define MICROMACHINES_CONVERTER_H

#include "../../common/Constants.h"
#include <tuple>
#include <cmath>

class Converter {
public:
    std::tuple<int, int> getLuaMapPosition(int pos_x, int pos_y, int matrixHeight, int matrixWidth);
};


#endif //MICROMACHINES_CONVERTER_H
