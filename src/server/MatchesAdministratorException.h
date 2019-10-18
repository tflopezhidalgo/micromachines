//
// Created by leobellaera on 15/10/19.
//

#ifndef MICROMACHINES_MATCHESADMINISTRATOREXCEPTION_H
#define MICROMACHINES_MATCHESADMINISTRATOREXCEPTION_H

#include <stdexcept>
#include <string>

class MatchesAdministratorException : public std::runtime_error {
public:
    explicit MatchesAdministratorException(std::string error) : runtime_error(error.c_str()) {}
};

#endif //MICROMACHINES_MATCHESADMINISTRATOREXCEPTION_H
