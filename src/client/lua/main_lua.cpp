#include "LuaScript.cpp"
#include <algorithm>
#include <vector>

int main(int argc, char* argv[]) {
    std::string map("map.lua");
    LuaScript* lua = new LuaScript(map);
    std::string action = lua->getAction(90, 2,2);

    for (int i = 0; i < newEntities.size(); i++) {
        auto it = std::find(entities.begin(), entities.end(), newEntities[i]);
        if (it == entities.end()) {
            entities.push_back(newEntities[i]);
        }
    }
    std::cout << "print action: "<< action << std::endl;
}