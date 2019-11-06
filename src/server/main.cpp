//
// Created by leobellaera on 12/10/19.
//

#include "LobbyClientAcceptor.h"
#include <map>
#include <iostream>
#include <Constants.h>

int main(int argc, char* argv[]) {
    MatchesAdministrator matchesAdministrator("../config.cfg");
    auto acceptor = new LobbyClientAcceptor(BACKLOG, argv[1], matchesAdministrator);
    acceptor->start();
    char c = '\0';
    while (c != 'q') {
        std::cin >> c;
    }
    acceptor->stop();
    acceptor->join();
    return 0;
}
