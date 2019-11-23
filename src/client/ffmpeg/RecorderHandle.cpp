#include "RecorderHandle.h"

#define EXTENSION ".mpeg"

RecorderHandle::RecorderHandle(ProtectedVector& pv) :
        recording(false),
        pv(pv),
        counter(0) {}

bool RecorderHandle::isRecording() {
    return recording;
}

void RecorderHandle::startRecorder() {
    if (!recording) {
        recording = true;
        pv.open();
        std::string fileName = std::string(GAME_NAME) + std::to_string(counter) + std::string(EXTENSION);
        recorders.push_back(new Recorder(WINDOW_WIDTH, WINDOW_HEIGHT, pv, fileName));
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
    while(recorders.size()) {
        Recorder* aux = recorders.back();
        aux->stop();
        recorders.pop_back();
        std::cout << "Valor de aux: " << aux << std::endl;
        delete aux;
    }

    recording = false;
}
