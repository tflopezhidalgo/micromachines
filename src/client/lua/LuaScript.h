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

public:
    LuaScript(std::string &mapName);

    std::string getAction(int angle, int pos_x, int pos_y);

    std::string getLastAction();

    void emptyStack();

    void luaCreateTable(std::vector<std::vector<int>> table, std::string typeTable);

    void createMap(std::vector<std::vector<int>> table);

    void setEntities(std::vector<std::vector<int>> table);

    ~LuaScript();
};


#endif //MICROMACHINES_LUASCRIPT_H
