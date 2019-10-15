//
// Created by leobellaera on 12/10/19.
//

#include "Socket.h"
#include "LobbyClientAcceptor.h"

int main() {
    LobbyClientAcceptor acceptor(5, "7777");
    acceptor.run();
    acceptor.join();
    return 0;
}
