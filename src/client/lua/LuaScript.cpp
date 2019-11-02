//
// Created by eliana on 30/10/19.
//
#include <iostream>
#include "LuaScript.h"

#define PLAYER_SCRIPT "player.lua"
#define ENTITIES_SCRIPT "entities_ids.lua"
#define MAP_SCRIPT "map.lua"

LuaScript::LuaScript() {
    L = luaL_newstate();
    luaL_openlibs(L);

    luaL_dofile(L, MAP_SCRIPT);
    luaL_dofile(L, PLAYER_SCRIPT);
    luaL_dofile(L, ENTITIES_SCRIPT);
}

const char* LuaScript::getAction(int angle, int pos_x, int pos_y) {
    int stackSize = lua_gettop(L);
    std::cout << "stacksize: " << stackSize << std::endl;

    // Agrego al stack la función a llamar
    lua_getglobal(L, "getAction");
    // Agrego al stack los parámetros de la función a llamar
    lua_pushnumber(L, angle);
    lua_pushnumber(L, pos_x);
    lua_pushnumber(L, pos_y);

    // Llamo a la función
    // La función recibe 2 parámetros y devuelve 1
    lua_pcall(L, 3, 1, 0);
    action = lua_tostring(L, 1);

    // Limpio el stack
    lua_pop(L, 1);
    stackSize = lua_gettop(L);
    std::cout << "stacksize: " << stackSize << std::endl;

    lastAction = (char*)action;
    return action;
}

char* LuaScript::getLastAction() {
    return lastAction;
}

void LuaScript::createTable(std::vector<std::vector<int>> mapVector) {
    lua_newtable(L);
    for (int i = 0; i < mapVector.size(); i++) {
        //lua_pushinteger(L, i + 1);
        //lua_pushnumber(L, mapVector[i]);
        //lua_settable(L, -3);
    }
}

LuaScript::~LuaScript() {
    int stackSize = lua_gettop(L);
    while(stackSize != 0) {
        lua_pop(L, 1);
        stackSize = lua_gettop(L);
    }
    lua_close(L);
}