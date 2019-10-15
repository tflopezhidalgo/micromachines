//
// Created by leobellaera on 13/10/19.
//

#ifndef MICROMACHINES_GAMESADMINISTRATOR_H
#define MICROMACHINES_GAMESADMINISTRATOR_H

#include <vector>
#include <string>
#include <mutex>
#include "Game.h"

class GamesAdministrator {
private:
    std::vector<Game*> games;
    std::mutex mutex;
public:
    GamesAdministrator();
    void createGame(std::string& creatorId, std::string& gameName,
            std::string& mapName, int playersAmount, int raceLaps);
    void joinClientToGame(std::string& gameName, std::string& clientId);
    ~GamesAdministrator();
};


#endif //MICROMACHINES_GAMESADMINISTRATOR_H
