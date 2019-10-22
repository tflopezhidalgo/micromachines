//
// Created by leobellaera on 14/10/19.
//

#ifndef MICROMACHINES_PROTOCOL_H
#define MICROMACHINES_PROTOCOL_H

#include "Socket.h"
#include <string>

class Protocol {
private:
    Socket socket;
public:
    explicit Protocol(Socket& socket);
    std::string receiveMessage();
    void sendMessage(std::string& message);
    ~Protocol();
};

#endif //MICROMACHINES_PROTOCOL_H
