#include "LuaScript.cpp"

int main(int argc, char* argv[]) {
    LuaScript* lua = new LuaScript();
    std::string action = lua->getAction(90, 2,2);

    std::cout << "print action: "<< action << std::endl;
}