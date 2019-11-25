#include "WinnerAnnunciator.h"

WinnerAnnunciator::WinnerAnnunciator(Window &w) :
w(w) { }

void WinnerAnnunciator::setWinners(std::vector<std::string> &winners) {
    int h = -650;
    Text text_winners(this->w, "../media/fonts/myFont.TTF", 60);
    SDL_Rect r = {(w.getWidth() - 650) / 2, (w.getHeight() + h) / 2, 650, 200};
    text_winners.setText("GANADORES");
    text_winners.setPositionAndSize(r);
    SDL_Color color = {255, 0, 0};
    text_winners.setColor(color);
    this->winners.push_back(std::move(text_winners));

    for (std::string& car : winners) {
        Text text(this->w, "../media/fonts/myFont.TTF", 60);
        text.setText(car);
        h += 350;
        SDL_Rect r = {(w.getWidth() - 400) / 2, (w.getHeight() + h) / 2, 400, 150};
        text.setPositionAndSize(r);
        this->winners.push_back(std::move(text));
    }
}

void WinnerAnnunciator::render() {
    if (winners.size() == 0) {
        return;
    }

    for (Text& winner : winners) {
        winner.render();
    }
}
