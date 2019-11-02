#include "LuaScript.cpp"

int main(int argc, char argv[]) {
    LuaScript lua("map.lua");

    std::string action = lua.getAction(1,1);

    std::cout << action << std::endl;
}