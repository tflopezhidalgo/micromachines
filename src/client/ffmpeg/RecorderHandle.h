#ifndef MICROMACHINES_RECORDERHANDLE_H
#define MICROMACHINES_RECORDERHANDLE_H


#include <bits/unique_ptr.h>
#include <iostream>
#include <memory>
#include "ProtectedVector.h"
#include "Recorder.h"
#include "Constants.h"

class RecorderHandle {
private:
    bool recording;
    std::unique_ptr<Recorder> recorder;
    ProtectedVector &pv;
    int counter;
public:
    explicit RecorderHandle(ProtectedVector& pv);

    void startRecorder();

    bool isRecording();

    void stopRecorder();

    ~RecorderHandle();
};


#endif //MICROMACHINES_RECORDERHANDLE_H
