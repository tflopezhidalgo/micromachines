#include "RecorderHandle.h"

#define EXTENSION ".mpeg"

RecorderHandle::RecorderHandle(ProtectedVector& pv, int w, int h) :
        recording(false),
        pv(pv),
        counter(0),
        width(w),
        height(h) {}

bool RecorderHandle::isRecording() {
    return recording;
}

void RecorderHandle::startRecorder() {
    if (!recording) {
        recording = true;
        pv.open();
        std::string fileName = std::string(GAME_NAME) + std::to_string(counter) + std::string(EXTENSION);
        recorders.push_back(new Recorder(width, height, pv, fileName));
        recorders[counter]->start();
    }
}

void RecorderHandle::stopRecorder() {
    if (recording) {
        recorders[counter]->stop();
        recorders[counter]->join();
        recording = false;
        counter++; // solo si ya esta cerrado el anterior puede crear un thread
    }
}

RecorderHandle::~RecorderHandle() {
    for (auto th: recorders) {
        if (th->isAlive()) {
            th->stop();
            th->join();
        }
        recording = false;
    }
}
