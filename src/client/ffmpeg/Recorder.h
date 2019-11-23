#ifndef MICROMACHINES_RECORDER_H
#define MICROMACHINES_RECORDER_H

#include "../../common/Thread.h"
#include "ProtectedVector.h"
#include "FormatContext.h"
#include "FrameWriter.h"
#include "../Window.h"
#include "Constants.h"
#include <zconf.h>

extern "C" {
#include <libswscale/swscale.h>
}

class Recorder : public Thread {
private:
    ProtectedVector& vectorFrames;
    FormatContext context;
    FrameWriter frameWriter;
    SwsContext* ctx;
    bool running;
public:
    Recorder(const int window_width, const int window_height, ProtectedVector& queueFrame, std::string& fileName);

    virtual void run() override;

    ~Recorder();

    void stop();
};


#endif //MICROMACHINES_RECORDER_H
