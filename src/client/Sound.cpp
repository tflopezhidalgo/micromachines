#include "Sound.h"

Sound::Sound(const std::string &file) {
    chunk = Mix_LoadWAV(file.c_str());
}

void Sound::play(int loops) {
    Mix_PlayChannel(-1, this->chunk, loops);
}

void Sound::setVolume(int volume) {
    Mix_VolumeChunk(this->chunk, volume);
}

Sound::~Sound() {
    Mix_FreeChunk(this->chunk);
}
