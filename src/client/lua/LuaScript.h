//
// Created by eliana on 30/10/19.
//

#ifndef MICROMACHINES_LUASCRIPT_H
#define MICROMACHINES_LUASCRIPT_H

#include <string>
#include <iostream>
#include <vector>

extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}

class LuaScript {
private:
    lua_State *L;
    std::string action;
public:
    LuaScript(std::string &mapName);

    std::string getAction(int angle, int pos_x, int pos_y);

    std::string getLastAction();

    ~LuaScript();
};


#endif //MICROMACHINES_LUASCRIPT_H
