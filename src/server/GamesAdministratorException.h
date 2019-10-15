//
// Created by leobellaera on 15/10/19.
//

#ifndef MICROMACHINES_GAMESADMINISTRATOREXCEPTION_H
#define MICROMACHINES_GAMESADMINISTRATOREXCEPTION_H

#include <stdexcept>
#include <string>

class GamesAdministratorException : public std::runtime_error {
public:
    explicit GamesAdministratorException(std::string error) : runtime_error(error.c_str()) {}
};

#endif //MICROMACHINES_GAMESADMINISTRATOREXCEPTION_H
