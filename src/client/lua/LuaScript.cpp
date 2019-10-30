//
// Created by eliana on 30/10/19.
//

#include "LuaScript.h"

LuaScript::LuaScript(const std::string &filename) {
    luaL_openlibs(L);
    luaL_dofile(L, filename);
}

std::string LuaScript::getAction(std::string car_id) {
    // Agrego al stack la función a llamar
    lua_getglobal(L, "getAction");
    // Agrego al stack los parámetros de la función a llamar
    lua_pushlstring(L, car_id, strlen(car_id.length()));
    //lua_pushnumber(L, numberHits);

    // Llamo a la función
    // lua_call(L, numParamsEntrada, numParamsSalida)
    // La función recibe 1 parámetros y devuelve 1
    lua_call(L, 1, 1);
    int damage = lua_tonumber(L, 1);

    // Limpio el stack
    lua_gettop(L);
}

LuaScript::~LuaScript() {
    int stackSize = lua_gettop(L);
    while(stackSize != 0) {
        lua_pop(L, 1);
        stackSize = lua_gettop(L);
    }
    lua_close(L);
}