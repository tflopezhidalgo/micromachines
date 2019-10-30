//
// Created by eliana on 30/10/19.
//

#ifndef MICROMACHINES_LUASCRIPT_H
#define MICROMACHINES_LUASCRIPT_H

#include <string>

extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib# include <lualib.h>
.h>
}

class LuaScript {
private:
    lua_State *L;
public:
    LuaScript(const std::string& filename);

    std::string getAction();

    ~LuaScript();
};


#endif //MICROMACHINES_LUASCRIPT_H
