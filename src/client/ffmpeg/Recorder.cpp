#include "Recorder.h"


Recorder::Recorder(const int window_width, const int window_height,
        ProtectedVector &pv, std::string& fileName) :
    vectorFrames(pv),
    frameWriter(context, fileName, window_width, window_height),
    ctx(sws_getContext(window_width, window_height,
                       AV_PIX_FMT_RGB24, window_width, window_height,
                       AV_PIX_FMT_YUV420P, 0, 0, 0, 0)),
                       running(true) {}

void Recorder::run() {
    int fixed_time = 1000/ 60; // seconds/frames
    try {
        while (running) {
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
            std::vector<char> frame;
            if (!this->vectorFrames.pop(frame)) return;
            frameWriter.write(frame.data(), ctx);

            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

            if (duration.count() < fixed_time) {
                std::this_thread::sleep_for(std::chrono::milliseconds(fixed_time - duration.count()));
            }

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
    running = false;
}

