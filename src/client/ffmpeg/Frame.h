#ifndef MICROMACHINES_FRAME_H
#define MICROMACHINES_FRAME_H

#include "RecorderException.h"

extern "C" {
#include "libswscale/swscale.h"
#include <libavutil/frame.h>
}

class Frame {
private:
    AVFrame* frame;
    int currentPts;
public:
    Frame(int pix_fmt, int width, int height);

    AVFrame* get();

    void write(const char *bufferData, SwsContext *ctx);

    ~Frame();
};


#endif //MICROMACHINES_FRAME_H
