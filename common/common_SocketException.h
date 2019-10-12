//
// Created by leobellaera on 26/9/19.
//

#ifndef TP_SOCKETEXCEPTION_H
#define TP_SOCKETEXCEPTION_H

#include <stdexcept>
#include <string>

class SocketException : public std::runtime_error {
public:
    explicit SocketException(std::string error) : runtime_error(error.c_str()) {}
};

#endif //TP_SOCKETEXCEPTION_H
