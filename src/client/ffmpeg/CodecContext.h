#ifndef MICROMACHINES_CODECCONTEXT_H
#define MICROMACHINES_CODECCONTEXT_H

#include "FormatContext.h"
#include "RecorderException.h"
#include <cstdio>
#include <string>
#include <stdexcept>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
}

class CodecContext {
private:
    AVCodecContext* codecContext;
public:
    explicit CodecContext(AVCodec* codec, int width, int height);

    AVCodecContext *get();

    int getHeight();

    int getWidth();

    int getPixFmt();

    ~CodecContext();
};


#endif //MICROMACHINES_CODECCONTEXT_H
