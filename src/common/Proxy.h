#ifndef MICROMACHINES_PROXY_H
#define MICROMACHINES_PROXY_H

#include "Socket.h"
#include <string>

class Proxy {
private:
    Socket socket;
public:
    explicit Proxy(Socket socket);
    Proxy(Proxy&& other) noexcept;
    std::string receiveMessage();
    void sendMessage(std::string& message);
    void stop();
    ~Proxy();
};

#endif //MICROMACHINES_PROXY_H
