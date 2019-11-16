#ifndef MICROMACHINES_FILEREADINGEXCEPTION_H
#define MICROMACHINES_FILEREADINGEXCEPTION_H

#include <stdexcept>

class FileReadingException : public std::runtime_error {
public:
    explicit FileReadingException(const char* error) : runtime_error(error) {}
};

#endif //MICROMACHINES_FILEREADINGEXCEPTION_H
