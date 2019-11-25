//
// Created by leobellaera on 12/10/19.
//

#include "LobbyClientAcceptor.h"
#include <iostream>
#include <Constants.h>
#include <SocketException.h>
#include <FileReadingException.h>

void closeThreads(MatchesAdministrator& matchesAdministrator, LobbyClientAcceptor& acceptor);

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << "Invalid use. Try: ./Server <port>" << std::endl;
        return 1;
    }

    MatchesAdministrator matchesAdministrator(CONFIG_PATH);
    LobbyClientAcceptor acceptor(BACKLOG, argv[1], matchesAdministrator);

    try {
        acceptor.start();
        matchesAdministrator.start();

        char c = '\0';
        while (c != 'q') {
            std::cin >> c;
        }

        closeThreads(matchesAdministrator, acceptor);
        return 0;

    } catch (const SocketException& e) {
        std::cout << e.what() << std::endl;
        closeThreads(matchesAdministrator, acceptor);
        return 1;
    } catch (const FileReadingException& e) {
        std::cout << e.what() << std::endl;
        closeThreads(matchesAdministrator, acceptor);
        return 1;
    } catch (...) {
        std::cout << "Unexpected error happened" << std::endl;
        closeThreads(matchesAdministrator, acceptor);
        return 1;
    }

}

void closeThreads(MatchesAdministrator& matchesAdministrator, LobbyClientAcceptor& acceptor) {
    matchesAdministrator.stop();
    matchesAdministrator.join();
    acceptor.stop();
    acceptor.join();
}