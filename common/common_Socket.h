//
// Created by leobellaera on 26/9/19.
//

#ifndef TP_SOCKET_H
#define TP_SOCKET_H
#include <netdb.h>

class Socket {
private:
    int fd;
    explicit Socket(int fd);
    int listen(int backlog);
    int bind(addrinfo* ptr);
    addrinfo* getAddrInfo(const char* host, const char* port, int flags);
    bool iterateAddrInfo(addrinfo* result, bool passive, int backlog);
    bool operationalizeSocket(addrinfo* ptr, int backlog, bool passive);
public:
    Socket(const char* host, const char* service);
    Socket(int backlog, const char* service);
    Socket(Socket &&other) noexcept;
    Socket accept();
    void sendMessage(const char* buffer, int size);
    void recvMessage(char* buffer, int size);
    void close();
    ~Socket();
};

#endif //TP_SOCKET_H
