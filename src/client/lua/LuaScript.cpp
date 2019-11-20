#include <iostream>
#include "LuaScript.h"

#define RELATIVE_PATH "../src/client/lua/"
#define ENTITIES_SCRIPT "../src/client/lua/entities_ids.lua"
#define FLOOR_SCRIPT "../src/client/lua/floor_ids.lua"
#define ENTITIES "entities"
#define MAP "map"
#define INDEX_X 1
#define INDEX_Y 2

LuaScript::LuaScript(std::string& clientId, std::string& scriptFile) :
    clientId(clientId){
    L = luaL_newstate();
    luaL_openlibs(L);

    std::string player = std::string(RELATIVE_PATH) + scriptFile;
    luaL_dofile(L, player.c_str());
    luaL_dofile(L, ENTITIES_SCRIPT);
    luaL_dofile(L, FLOOR_SCRIPT);
}

/* Envia por el stack los parametros de la funcion
 * Recibe string con el movimiento a realizar
 */
Event LuaScript::getEvent(int angle, int pos_x, int pos_y) {
    auto tuplePos = converter.getLuaMapPosition(pos_x, pos_y,
            matrixHeight, matrixWidth);

    int ang = abs(round(angle));
    lua_getglobal(L, "getEvent");
    lua_pushnumber(L, ang);
    lua_pushnumber(L, std::get<0>(tuplePos));
    lua_pushnumber(L, std::get<1>(tuplePos));
    lua_pushnumber(L, pos_x);
    lua_pushnumber(L, pos_y);

    lua_pcall(L, 3, 1, 0);
    const char* luaEvent = lua_tostring(L, 1);
    lua_pop(L, 1); // elimina lua_action

    return std::move(createEvent(luaEvent));
}

/* Crea un evento a partir del string devuelto por sl scriptLua */
Event LuaScript::createEvent(const char* luaEvent) {
    std::vector<char> v_event;
    action = std::string(luaEvent);

    if (action[0] == FORWARD) count_turns = 0;

    v_event.push_back(action[0]);
    if (action[0] == RIGHT || action[0] == LEFT) {
        count_turns++;
        if (count_turns == 12) {
            v_event.push_back(FORWARD);
            count_turns = 0;
        }
    }

    Event event(clientId, v_event);
    return std::move(event);
}

/* Crea una tabla en lua que es guardada en el stack
 * para ser usada por el script
 */
void LuaScript::luaCreateTable(std::vector<std::vector<int>> table, std::string typeTable) {
    lua_newtable(L);
    for(int i = 0; i < table.size(); i++) {
        lua_pushnumber(L, i + 1);    // indice de la tabla
        lua_newtable(L);                    // tabla
        int size = table[i].size();
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

/* Libera el stack de lua */
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