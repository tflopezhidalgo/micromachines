#ifndef MICROMACHINES_MUSIC_H
#define MICROMACHINES_MUSIC_H

#include <SDL2/SDL_mixer.h>
#include <string>

class Music {
private:
    Mix_Music* musicPtr;

public:
    explicit Music(const std::string& file);
    void play();
    ~Music();
};


#endif
