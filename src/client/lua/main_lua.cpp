#include "LuaScript.h"
#include <vector>

int main(int argc, char* argv[]) {
    std::string map("map.lua");
    LuaScript lua;

    std::vector<std::vector<int>> vector;
    std::vector<int> v = {1, 0, 0};
    vector.push_back(v);

    //lua->setEntities(vector);
    //lua->luaCreateTable(vector, "map"); // entities
    std::string action = lua.getAction(90, 0,0);

    std::cout << "print action: "<< action << std::endl;
}