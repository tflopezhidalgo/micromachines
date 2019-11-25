#include "Sound.h"

Sound::Sound(const std::string &file) {
    chunk = Mix_LoadWAV(file.c_str());
    this->channel = -1;
}

void Sound::play(int loops) {
    this->channel = Mix_PlayChannel(-1, this->chunk, loops);
}

void Sound::setVolume(int volume) {
    Mix_VolumeChunk(this->chunk, volume);
}

void Sound::stop() {
    Mix_HaltChannel(this->channel);
}

Sound::~Sound() {
    Mix_FreeChunk(this->chunk);
}
