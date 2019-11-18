#include "Recorder.h"

Recorder::Recorder(Window &window, BlockQueue &queueFrames, std::string& fileName) :
    queueFrames(queueFrames),
    frameWriter(context, fileName, window.getWidth(), window.getHeight()),
    ctx(sws_getContext(window.getWidth(), window.getHeight(),
                       AV_PIX_FMT_RGB24, window.getWidth(), window.getHeight(),
                       AV_PIX_FMT_YUV420P, 0, 0, 0, 0)){
    av_register_all();
    }

void Recorder::run() {
    try {
        std::vector<char> frame;
        while (this->queueFrames.pop(frame)) {
            frameWriter.write(frame.data(), ctx);
        }
    } catch (RecorderException& e) {
        frameWriter.close();
        return;
    }
    frameWriter.close();
}

Recorder::~Recorder() {
    queueFrames.close();
    sws_freeContext(ctx);
}
