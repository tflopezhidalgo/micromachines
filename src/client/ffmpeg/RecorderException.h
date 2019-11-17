#ifndef MICROMACHINES_OUPUTFORMATEXCEPTION_H
#define MICROMACHINES_OUPUTFORMATEXCEPTION_H

#include <stdexcept>
#include <string>

class RecorderException : public std::runtime_error {
public:
    explicit RecorderException(const char* error) : runtime_error(error)  {}
};


#endif //MICROMACHINES_OUPUTFORMATEXCEPTION_H
