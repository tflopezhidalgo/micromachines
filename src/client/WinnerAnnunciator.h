#ifndef MICROMACHINES_WINNERANNUNCIATOR_H
#define MICROMACHINES_WINNERANNUNCIATOR_H

#include <vector>
#include "Text.h"

class WinnerAnnunciator {
private:
    std::vector<Text> winners;
    Window& w;

public:
    explicit WinnerAnnunciator(Window& w);
    void setWinners(std::vector<std::string>& winners);
    void render();
};


#endif
