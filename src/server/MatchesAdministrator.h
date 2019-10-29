//
// Created by leobellaera on 13/10/19.
//

#ifndef MICROMACHINES_MATCHESADMINISTRATOR_H
#define MICROMACHINES_MATCHESADMINISTRATOR_H

#include <unordered_map>
#include <string>
#include <mutex>
#include "Match.h"
#include "../common/Proxy.h"
#include "ConfigMapBuilder.h"

class MatchesAdministrator {
private:
    std::unordered_map<std::string, Match*> matches;
    ConfigMapBuilder configMapBuilder;
    std::mutex mutex;
public:
    explicit MatchesAdministrator(const char* configPath);
    bool createMatch(std::string& creatorNickname,
            Proxy clientProxy,
            std::string& matchName,
            std::string& mapName,
            int playersAmount,
            int raceLaps);
    bool addClientToMatch(std::string& clientNickname,
                          Proxy& clientProxy,
                          std::string& matchName);
    void deleteFinishedMatches();
    std::string getAvailableMatches();
    ~MatchesAdministrator();
};

#endif //MICROMACHINES_MATCHESADMINISTRATOR_H
