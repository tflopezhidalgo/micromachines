//
// Created by leobellaera on 12/10/19.
//

#include "LobbyClientAcceptor.h"
#include <iostream>
#include <Constants.h>
#include <SocketException.h>
#include <FileReadingException.h>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cout << "Invalid use. Try: ./Server <port>" << std::endl;
        return 1;
    }

    try {
        MatchesAdministrator matchesAdministrator(CONFIG_PATH);
        LobbyClientAcceptor acceptor(BACKLOG, argv[1], matchesAdministrator);
        acceptor.start();
        matchesAdministrator.start();

        char c = '\0';
        while (c != 'q') {
            std::cin >> c;
        }

        matchesAdministrator.stop();
        matchesAdministrator.join();
        acceptor.stop();
        acceptor.join();

        return 0;

    } catch (const SocketException& e) {
        std::cout << e.what() << std::endl;
        return 1;
    } catch (const FileReadingException& e) {
        std::cout << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unexpected error happened" << std::endl;
        return 1;
    }

}
