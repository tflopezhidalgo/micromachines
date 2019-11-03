//
// Created by eliana on 30/10/19.
//

#ifndef MICROMACHINES_LUASCRIPT_H
#define MICROMACHINES_LUASCRIPT_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}

class LuaScript {
private:
    lua_State *L;
    std::string action;
    std::vector<std::vector<int>> entities;

    std::vector<std::vector<int>> addedEntities(
            std::vector<std::vector<int>> newEntities);

    std::vector<std::vector<int>> deletedEntities(
            std::vector<std::vector<int>> newEntities);

    void createTable(std::vector<std::vector<int>> newEntities);
public:
    LuaScript(std::string &mapName);

    std::string getAction(int angle, int pos_x, int pos_y);

    std::string getLastAction();

    void setEntitiesTable(std::vector<std::vector<int>> entitiesVector);

    ~LuaScript();
};


#endif //MICROMACHINES_LUASCRIPT_H
