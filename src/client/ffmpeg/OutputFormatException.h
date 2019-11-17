#ifndef MICROMACHINES_OUPUTFORMATEXCEPTION_H
#define MICROMACHINES_OUPUTFORMATEXCEPTION_H

#include <stdexcept>
#include <string>

class OutputFormatException : public std::runtime_error {
public:
    explicit OutputFormatException(const char* error) : runtime_error(error)  {}
};


#endif //MICROMACHINES_OUPUTFORMATEXCEPTION_H
