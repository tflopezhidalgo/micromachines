//
// Created by leobellaera on 26/9/19.
//

#include "common_Socket.h"
#include "common_SocketException.h"
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <cstdlib>

#define SEND_ERROR_MSG "Error while trying to send message\n"
#define RECV_ERROR_MSG "Error while trying to receive message\n"
#define ACCEPT_ERROR_MSG "Error while trying to accept client\n"

#define CONNECT_ERROR_MSG "Error while trying to establish connection\n"
#define BIND_AND_LISTEN_ERR_MSG "Error while trying to bind and listen\n"

Socket::Socket(const char* host, const char* service) :
    fd(-1) {
    addrinfo* addrInfo = this->getAddrInfo(host, service, 0);
    bool success = this->iterateAddrInfo(addrInfo, false, 0);
    freeaddrinfo(addrInfo);
    if (!success) {
        this->close();
        throw SocketException(CONNECT_ERROR_MSG);
    }
}

Socket::Socket(int backlog, const char* service) :
    fd(-1) {
    addrinfo* addrInfo = this->getAddrInfo(nullptr, service, AI_PASSIVE);
    bool success = this->iterateAddrInfo(addrInfo, true, backlog);
    freeaddrinfo(addrInfo);
    if (!success) {
        this->close();
        throw SocketException(BIND_AND_LISTEN_ERR_MSG);
    }
}

Socket::Socket(int fd) :
    fd(fd) {}

Socket::Socket(Socket &&other) noexcept {
    this->fd = other.fd;
    other.fd = -1;
}

Socket Socket::accept() {
    int peer_fd = ::accept(fd, nullptr, nullptr);
    if (peer_fd == -1){
        throw SocketException(ACCEPT_ERROR_MSG);
    }
    return std::move(Socket(peer_fd));
}

addrinfo* Socket::getAddrInfo(const char* host,
        const char* port, int flags) {
    struct addrinfo* addr_info;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = flags;
    int s = getaddrinfo(host, port, &hints, &addr_info);
    if (s != 0) {
        std::string err = std::string("Error in getaddrinfo: ")
                + gai_strerror(s) + '\n';
        throw SocketException(err);
    }
    return addr_info;
}

void Socket::sendMessage(const char* buffer, int size) {
    int sent = 0;
    int s = 0;
    while (sent < size) {
        s = send(fd, &buffer[sent], size - sent, MSG_NOSIGNAL);
        if (s == 0 || s == -1) {
            throw SocketException(SEND_ERROR_MSG);
        } else {
            sent += s;
        }
    }
}

void Socket::recvMessage(char* buffer, int size) {
    int received = 0;
    int s = 0;
    while (received < size) {
        s = recv(fd, &buffer[received], size-received, 0);
        if (s == 0 || s == -1) {
            throw SocketException(RECV_ERROR_MSG);
        } else {
            received += s;
        }
    }
}

int Socket::bind(addrinfo* ptr) {
    int s = ::bind(fd, ptr->ai_addr, ptr->ai_addrlen);
    if (s == -1) {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        return -1;
    }
    return 0;
}

int Socket::listen(int backlog) {
    int s = ::listen(fd, backlog);
    if (s == -1) {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        return -1;
    }
    return 0;
}

bool Socket::iterateAddrInfo(addrinfo* result, bool passive, int backlog) {
    struct addrinfo* ptr;
    bool success = false;
    for (ptr = result; ptr != nullptr && !success ; ptr = ptr->ai_next) {
        fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (fd == -1) {
            std::cerr << "Error: " << strerror(errno) << std::endl;
        } else {
            success = operationalizeSocket(ptr, backlog, passive);
        }
    }
    return success;
}

bool Socket::operationalizeSocket(addrinfo* ptr, int backlog, bool passive) {
    bool success;
    if (passive) {
        success = (bind(ptr) == 0 && listen(backlog) == 0);
    } else {
        success = (::connect(fd, ptr->ai_addr, ptr->ai_addrlen) != -1);
        if (!success) {
            std::cerr << "Error: " << strerror(errno) << std::endl;
        }
    }
    return success;
}

void Socket::close() {
    if (fd != -1) {
        shutdown(fd, SHUT_RDWR);
        ::close(fd);
        fd = -1;
    }
}

Socket::~Socket() {
    this->close();
}
