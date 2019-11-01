//
// Created by eliana on 30/10/19.
//

#ifndef MICROMACHINES_LUASCRIPT_H
#define MICROMACHINES_LUASCRIPT_H

#include <string>

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
    LuaScript(const std::string& map);

    std::string getAction(int pos_x, int pos_y);

    ~LuaScript();
};


#endif //MICROMACHINES_LUASCRIPT_H
