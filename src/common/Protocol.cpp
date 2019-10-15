//
// Created by leobellaera on 14/10/19.
//

#include <arpa/inet.h>
#include <vector>
#include "Protocol.h"

#define UINT32_SIZE 4

Protocol::Protocol(Socket& socket) :
    socket(std::move(socket)) {}

std::string Protocol::receiveMessage() {
    uint32_t msgLength = 0;
    socket.recvMessage((char*)&msgLength, UINT32_SIZE);
    msgLength = ntohl(msgLength);

    std::vector<char> msg_buffer(msgLength);
    socket.recvMessage(msg_buffer.data(), msgLength);
    std::string msg(msg_buffer.data(), msgLength);
    return std::move(msg);
}

void Protocol::sendMessage(std::string& msg) {
    uint32_t length = htonl(msg.length());
    socket.sendMessage((char*)&length, UINT32_SIZE);
    socket.sendMessage(msg.c_str(), msg.length());
}

Protocol::~Protocol() {
    //close socket
}
