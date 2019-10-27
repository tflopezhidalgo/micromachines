#ifndef MICROMACHINES_ACTION_H
#define MICROMACHINES_ACTION_H

#include <string>
#include <nlohmann/json.hpp>

#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define QUIT 'Q'
#define NO_OP 'A'

class Action {
    private:
        char action;

    public:
        Action(char action);
        Action(Action&& other);
        std::string dump();
        bool isNoOp();
};


#endif
