#include "RecorderHandle.h"

#define EXTENSION ".mpeg"

RecorderHandle::RecorderHandle(ProtectedVector& pv) :
    recording(false),
    pv(pv),
    counter(0) {
    av_register_all();
}

bool RecorderHandle::isRecording() {
    return recording;
}

void RecorderHandle::startRecorder() {
    recording = true;

    std::string fileName = std::string(GAME_NAME) + std::to_string(counter) + std::string(EXTENSION);
    recorder.reset(new Recorder(WINDOW_WIDTH, WINDOW_HEIGHT, pv, fileName));
    counter++;
}

void RecorderHandle::stopRecorder() {
    if (recording) {
        recorder->stop();
        recorder->join();
        recorder.reset();
        recording = false;
    }
}

RecorderHandle::~RecorderHandle() {
    stopRecorder();
}
