//
// Created by eliana on 30/10/19.
//
#include <iostream>
#include "LuaScript.h"

#define PLAYER_SCRIPT "player.lua"
#define ENTITIES_SCRIPT "entities_ids.lua"
#define FLOOR_SCRIPT "floor_ids.lua"
#define ENTITIES "entities"
#define MAP "map"
#define INDEX_X 1
#define INDEX_Y 2

LuaScript::LuaScript(std::string& clientId) :
    clientId(clientId) {
    L = luaL_newstate();
    luaL_openlibs(L);

    luaL_dofile(L, PLAYER_SCRIPT);
    luaL_dofile(L, ENTITIES_SCRIPT);
    luaL_dofile(L, FLOOR_SCRIPT);
}

Event LuaScript::getEvent(int angle, int pos_x, int pos_y) {
    auto tuplePos = converter.getLuaMapPosition(pos_x, pos_y,
            matrixHeight, matrixWidth);

    int ang = (int)round(angle/1000);
    std::cout << ang;
    lua_getglobal(L, "getEvent");
    lua_pushnumber(L, ang);
    lua_pushnumber(L, std::get<0>(tuplePos));
    lua_pushnumber(L, std::get<1>(tuplePos));

    lua_pcall(L, 3, 1, 0);
    const char* luaEvent = lua_tostring(L, 1);
    lua_pop(L, 1); // elimina lua_action

    //int stackSize = lua_gettop(L);
    //std::cout << stackSize << std::endl;
    //lua_pop(L, 1); // elimina entities
    std::cout << "Se genero ";
    std::vector<char> v_event;
    action = std::string(luaEvent);
    std::cout << "action: " <<action << action[0];

    //std::cout << luaEvent[0] << "-" << std::string(luaEvent).c_str() << std::endl;
    v_event.push_back('F');
    Event event(clientId, v_event);
    return std::move(event);
    //return createEvent(luaEvent);
}

Event LuaScript::createEvent(const char* luaEvent) {
    std::vector<char> v_event;
    std::cout << *luaEvent << "-" << std::string(luaEvent).c_str() << "-" << std::string(luaEvent) << std::endl;
    v_event.push_back(*luaEvent);
    Event event(clientId, v_event);
    return std::move(event);
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
        auto tuplePos = converter.getLuaMapPosition(
                table[i][INDEX_X],table[i][INDEX_Y],
                matrixHeight,matrixWidth);

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