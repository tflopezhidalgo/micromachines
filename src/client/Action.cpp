#include "Action.h"
#include <nlohmann/json.hpp>

Action::Action(char action) {
    this->action = action;
}

Action::Action(Action&& other) {
    this->action = std::move(other.action);
}

std::string Action::dump() {
    nlohmann::json j;
    j["action"] = this->action;
    return std::move(j.dump());
}

bool Action::isNoOp() {
    return (this->action == NO_OP);
}
