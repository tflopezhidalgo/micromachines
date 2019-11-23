#include "Music.h"
#include <stdexcept>

Music::Music(const std::string &file) {
    this->musicPtr = Mix_LoadMUS(file.c_str());

    if (musicPtr == NULL)
        throw std::runtime_error("Fallo al abrir archivo de musica");
}

void Music::play(int loop = 0) {
    Mix_PlayMusic(this->musicPtr, loop);
}

Music::~Music() {
    Mix_FreeMusic(this->musicPtr);
}
