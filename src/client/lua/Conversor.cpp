//
// Created by eliana on 5/11/19.
//

#include "Conversor.h"

int Conversor::pixel_to_position(int value) {
    int new_value = 0;

    15*50 = total_x = 750
    11*50 = total_y = 550

    total_x / 2 = 375 = ref_center_x
    total_y / 2 = 275 = ref_center_y

    ejemplo:
    pos_x = 330
    pos_y = 10

    la posicion en lua va a ser:

    pos_x + ref_center_x = real_pos_x
    pos_y + ref_center_y = real_pos_y

    real_pos_x / 15 = lua_x
    real_pos_y / 11 = lua_y
}
