//
// Created by eliana on 30/10/19.
//
#include <iostream>
#include "LuaScript.h"

#define PLAYER_SCRIPT "player.lua"
#define ENTITIES_SCRIPT "entities_ids.lua"
#define FLOOR_SCRIPT "floor_ids.lua"
#define MAP_SCRIPT "map.lua"
#define ENTITIES "entities"
#define MAP "map"
#define INDEX_X 1
#define INDEX_Y 2

LuaScript::LuaScript() {
    L = luaL_newstate();
    luaL_openlibs(L);

    luaL_dofile(L, MAP_SCRIPT);
    luaL_dofile(L, PLAYER_SCRIPT);
    luaL_dofile(L, ENTITIES_SCRIPT);
    luaL_dofile(L, FLOOR_SCRIPT);
}

std::string LuaScript::getAction(int angle, int pos_x, int pos_y) {
    auto tuplePos = converter.getLuaMapPosition(pos_x, pos_y,
            matrixHeight, matrixWidth);

    lua_getglobal(L, "getAction");
    lua_pushnumber(L, angle);
    lua_pushnumber(L, std::get<0>(tuplePos));
    lua_pushnumber(L, std::get<1>(tuplePos));

    lua_pcall(L, 3, 1, 0);
    const char* lua_action = lua_tostring(L, 1);

    emptyStack();
    action = std::string(lua_action);
    return action;
}

std::string LuaScript::getLastAction() {
    return action;
}

void LuaScript::luaCreateTable(std::vector<std::vector<int>> table, std::string typeTable) {
    lua_newtable(L);
    for(int i = 0; i < table.size(); i++) {
        lua_pushnumber(L, i + 1);    // indice de la tabla
        lua_newtable(L);                    // tabla

        int size = table[i].size();
        //if (typeTable == ENTITIES) size -= 1;

        for(int j = 0; j < size; j++) {
            lua_pushnumber(L, j + 1);       // indice del valor
            lua_pushnumber(L, table[i][j]);     // valor
            lua_settable(L, -3);
        }
        lua_settable( L, -3 );
    }
    lua_setglobal(L, typeTable.c_str());
}

void LuaScript::createMap(std::vector<std::vector<int>> table) {
    matrixHeight = table.size();
    matrixWidth = table[0].size();
    luaCreateTable(table, MAP);
}

void LuaScript::setEntities(std::vector<std::vector<int>> table) {
    for (int i = 0; i < table.size(); i++) {
        auto tuplePos = converter.getLuaMapPosition(table[i][INDEX_X], table[i][INDEX_Y],
                                                    matrixHeight, matrixWidth);
        table[i][INDEX_X] = std::get<0>(tuplePos);
        table[i][INDEX_Y] = std::get<1>(tuplePos);
    }
    luaCreateTable(table, ENTITIES);
}


void LuaScript::emptyStack() {
    int stackSize = lua_gettop(L);
    while(stackSize != 0) {
        lua_pop(L, 1);
        stackSize = lua_gettop(L);
    }
}

LuaScript::~LuaScript() {
    emptyStack();
    lua_close(L);
}