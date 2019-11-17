#ifndef MICROMACHINES_LUASCRIPT_H
#define MICROMACHINES_LUASCRIPT_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include "Converter.h"
#include "../../common/Event.h"

extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}

class LuaScript {
private:
    lua_State *L;
    std::string& clientId;
    Converter converter;
    std::string action;
    int matrixHeight;
    int matrixWidth;
    int count_turns;
    std::string last_action;

    void luaCreateTable(std::vector<std::vector<int>> table, std::string typeTable);

    void emptyStack();
public:
    explicit LuaScript(std::string& clientId);

    Event getEvent(int angle, int pos_x, int pos_y);

    void createMap(std::vector<std::vector<int>> table);

    void setEntities(std::vector<std::vector<int>> table);

    ~LuaScript();

    Event createEvent(const char *luaEvent);
};


#endif //MICROMACHINES_LUASCRIPT_H
