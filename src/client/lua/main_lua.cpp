#include "LuaScript.cpp"
#include <algorithm>
#include <vector>

int main(int argc, char* argv[]) {
    std::string map("map.lua");
    LuaScript* lua = new LuaScript(map); // no recibe mapa, el mapa lo crea
    lua->luaCreateTable(vector, "map"); // entities
    std::string action = lua->getAction(90, 2,2);

    std::cout << "print action: "<< action << std::endl;
}