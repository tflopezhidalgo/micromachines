//
// Created by leobellaera on 13/10/19.
//

#ifndef MICROMACHINES_MATCHESADMINISTRATOR_H
#define MICROMACHINES_MATCHESADMINISTRATOR_H

#include <vector>
#include <string>
#include <mutex>
#include "Match.h"

class MatchesAdministrator {
private:
    std::vector<Match*> matches;
    std::mutex mutex;
public:
    MatchesAdministrator();
    void createMatch(std::string& creatorId, std::string& matchName,
            std::string& mapName, int playersAmount, int raceLaps);
    void joinClientToMatch(std::string& matchName, std::string& clientId);
    ~MatchesAdministrator();
};

#endif //MICROMACHINES_MATCHESADMINISTRATOR_H
