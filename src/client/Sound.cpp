#include "Sound.h"

Sound::Sound(const std::string &file) {
    chunk = Mix_LoadWAV(file.c_str());
}

void Sound::play(int loops) {
    Mix_PlayChannel(-1, this->chunk, loops);
}

Sound::~Sound() {
    Mix_FreeChunk(this->chunk);
}
