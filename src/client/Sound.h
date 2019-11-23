#ifndef MICROMACHINES_SOUND_H
#define MICROMACHINES_SOUND_H

#include <SDL2/SDL_mixer.h>
#include <string>

class Sound {
private:
    Mix_Chunk* chunk;

public:
    explicit Sound(const std::string& file);
    void play(int loops = 0);
    ~Sound();

};


#endif
