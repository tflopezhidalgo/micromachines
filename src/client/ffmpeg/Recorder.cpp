#include "Recorder.h"


Recorder::Recorder(const int window_width, const int window_height,
        ProtectedVector &queueFrames, std::string& fileName) :
    queueFrames(queueFrames),
    frameWriter(context, fileName, window_width, window_height),
    ctx(sws_getContext(window_width, window_height,
                       AV_PIX_FMT_RGB24, window_width, window_height,
                       AV_PIX_FMT_YUV420P, 0, 0, 0, 0)){
    }

void Recorder::run() {
    std::cout << "recorder";
    try {
        std::vector<char> frame;
        while (this->queueFrames.pop(frame)) {
            frameWriter.write(frame.data(), ctx);
        }
    } catch (RecorderException& e) {
        return;
    }
}

Recorder::~Recorder() {
    frameWriter.close();
    sws_freeContext(ctx);
}

void Recorder::stop() {
    queueFrames.close();
}
