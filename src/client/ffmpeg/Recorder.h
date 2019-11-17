#ifndef MICROMACHINES_RECORDER_H
#define MICROMACHINES_RECORDER_H

#include "../../common/Thread.h"
#include "BlockQueue.h"
#include "FormatContext.h"
#include "FrameWriter.h"
#include "../Window.h"

extern "C" {
#include <libswscale/swscale.h>
}

class Recorder : public Thread {
private:
    BlockQueue& queueFrames;
    FormatContext context;
    FrameWriter frameWriter;
    SwsContext* ctx;

public:
    Recorder(Window& window, BlockQueue& queueFrame, std::string& fileName);

    virtual void run() override;

    ~Recorder();
};


#endif //MICROMACHINES_RECORDER_H
