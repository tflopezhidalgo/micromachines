//
// Created by leobellaera on 12/10/19.
//

#include "LobbyClientAcceptor.h"
#include <iostream>
#include <Constants.h>

int main(int argc, char* argv[]) {
    MatchesAdministrator matchesAdministrator("../config.cfg");
    LobbyClientAcceptor acceptor(BACKLOG, argv[1], matchesAdministrator);
    //todo matchesAdministrator.deleteFinishedMatches(); (another thread)
    acceptor.start();
    char c = '\0';
    while (c != 'q') {
        std::cin >> c;
    }
    acceptor.stop();
    acceptor.join();
    return 0;

}
