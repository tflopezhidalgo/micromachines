//
// Created by eliana on 30/10/19.
//
#include <iostream>
#include "LuaScript.h"

#define PLAYER_SCRIPT "player.lua"
#define ENTITIES_SCRIPT "entities_ids.lua"
#define MAP_SCRIPT "map.lua"

LuaScript::LuaScript(std::string &mapName) {
    L = luaL_newstate();
    luaL_openlibs(L);

    luaL_dofile(L, MAP_SCRIPT);
    luaL_dofile(L, PLAYER_SCRIPT);
    luaL_dofile(L, ENTITIES_SCRIPT);
}

std::string LuaScript::getAction(int angle, int pos_x, int pos_y) {
    lua_getglobal(L, "getAction");

    lua_pushnumber(L, angle);
    lua_pushnumber(L, pos_x);
    lua_pushnumber(L, pos_y);

    lua_pcall(L, 3, 1, 0);
    const char* lua_action = lua_tostring(L, 1);

    emptyStack();
    action = std::string(lua_action);
    return action;
}

std::string LuaScript::getLastAction() {
    return action;
}

void LuaScript::setEntitiesTable(std::vector<std::vector<int>> newEntities) {
    //int old_size = entities.size();
    std::vector<std::vector<int>> to_add = addedEntities(newEntities);
    std::vector<std::vector<int>> to_delete = deletedEntities(newEntities);

    luaCreateTable(newEntities);
    /*
    if (old_size == 0) {
        luaCreateTable(newEntities);
    } else {
        luaUpdateTable(newEntities);
    }
    */
}

void LuaScript::luaUpdateTable(std::vector<std::vector<int>> newEntities) {
    std::vector<std::vector<int>> to_add = addedEntities(newEntities);
    std::vector<std::vector<int>> to_delete = deletedEntities(newEntities);

    lua_getglobal(L,"entities");
    //lua_rawgeti(L,-1,1);
    //lua_rawgeti(L,-1,2);
}

void LuaScript::luaCreateTable(std::vector<std::vector<int>> newEntities) {
    lua_newtable(L);
    for(int i = 0; i < newEntities.size(); i++) {
        lua_pushnumber(L, i + 1);    // parent table index
        lua_newtable(L);             // child table
        for(int j = 0; j < newEntities[i].size(); j++) {
            lua_pushnumber(L, j + 1);  // this will be the child's index
            lua_pushnumber(L, newEntities[i][j]);  // this will be the child's value
            lua_settable(L, -3);
        }
        lua_settable( L, -3 );
    }
    lua_setglobal(L, "entities");
}

std::vector<std::vector<int>> LuaScript::addedEntities(
        std::vector<std::vector<int>> newEntities) {
    std::vector<std::vector<int>> different;
    for (int i = 0; i < newEntities.size(); i++) {
        auto it = std::find(entities.begin(), entities.end(), newEntities[i]);
        if (it == entities.end()) {
            entities.push_back(newEntities[i]);
            different.push_back(newEntities[i]);
        }
    }
    return different;
}

std::vector<std::vector<int>> LuaScript::deletedEntities(
        std::vector<std::vector<int>> newEntities) {
    std::vector<std::vector<int>> different;
    for (int i = 0; i < entities.size(); i++) {
        auto it = std::find(newEntities.begin(), newEntities.end(), entities[i]);
        if (it == newEntities.end()) {
            different.push_back(entities[i]);
        }
    }
    return different;
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