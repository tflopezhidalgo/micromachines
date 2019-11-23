#include "RecorderHandle.h"
#include <cerrno>

#define EXTENSION ".mpeg"

RecorderHandle::RecorderHandle(ProtectedVector& pv) :
        recording(false),
        pv(pv),
        counter(0) {
}

bool RecorderHandle::isRecording() {
    return recording;
}

void RecorderHandle::startRecorder() {
    if (!recording) {
        recording = true;
        std::string fileName = std::string(GAME_NAME) + std::to_string(counter) + std::string(EXTENSION);
        recorder.reset(new Recorder(WINDOW_WIDTH, WINDOW_HEIGHT, pv, fileName));
        recorder->start();
        counter++;
    }
}

void RecorderHandle::stopRecorder() {
    if (recording) {
        recorder->stop();
        std::perror("stop");
        //recorder->join();
        std::perror("join");
        recorder.reset(nullptr);
        std::perror("reset");
        recording = false;
    }
}

RecorderHandle::~RecorderHandle() {
    stopRecorder();
}