//
// Created by leobellaera on 13/10/19.
//

#ifndef MICROMACHINES_LOBBYGAMESORGANIZER_H
#define MICROMACHINES_LOBBYGAMESORGANIZER_H

#include <vector>
#include <string>
#include <mutex>

class LobbyGamesOrganizer {
private:
    //std::vector<Game*> games;
    std::mutex mutex;
public:
    LobbyGamesOrganizer();
    void createGame(std::string& creatorId, std::string& gameName,
            std::string& mapName, int playersAmount, int raceLaps);
    void joinClientToGame(std::string& gameName, std::string& clientId);
    ~LobbyGamesOrganizer();
};


#endif //MICROMACHINES_LOBBYGAMESORGANIZER_H
