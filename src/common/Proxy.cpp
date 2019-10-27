//
// Created by leobellaera on 14/10/19.
//

#include <arpa/inet.h>
#include <vector>
#include "Proxy.h"

#define UINT32_SIZE 4

Proxy::Proxy(Socket socket) :
    socket(std::move(socket)) {}

Proxy::Proxy(Proxy&& other) noexcept :
    socket(std::move(other.socket)) {}

std::string Proxy::receiveMessage() {
    uint32_t msgLength = 0;
    socket.recvMessage((char*)&msgLength, UINT32_SIZE);
    msgLength = ntohl(msgLength);

    std::vector<char> msg_buffer(msgLength);
    socket.recvMessage(msg_buffer.data(), msgLength);
    std::string msg(msg_buffer.data(), msgLength);
    return std::move(msg);
}

void Proxy::sendMessage(std::string& msg) {
    uint32_t length = htonl(msg.length());
    socket.sendMessage((char*)&length, UINT32_SIZE);
    socket.sendMessage(msg.c_str(), msg.length());
}

void Proxy::stop() {
    socket.close();
}

Proxy::~Proxy() {
    socket.close();
}
