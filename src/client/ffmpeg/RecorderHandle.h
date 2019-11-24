#ifndef MICROMACHINES_RECORDERHANDLE_H
#define MICROMACHINES_RECORDERHANDLE_H


#include <bits/unique_ptr.h>
#include "ProtectedVector.h"
#include "Recorder.h"
#include "Constants.h"

class RecorderHandle {
private:
    bool recording;
    std::vector<Recorder*> recorders;
    ProtectedVector &pv;
    int counter;
    int width;
    int height;
public:
    explicit RecorderHandle(ProtectedVector& pv, int w, int h);

    void startRecorder();

    void stopRecorder();

    bool isRecording();

    ~RecorderHandle();
};


#endif //MICROMACHINES_RECORDERHANDLE_H
