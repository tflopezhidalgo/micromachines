#ifndef MICROMACHINES_CODECONTEXT_H
#define MICROMACHINES_CODECONTEXT_H

#include "FormatContext.h"
#include <cstdio>
#include <string>
#include <stdexcept>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
}

class CodeContext {
private:
    AVCodecContext* codecContext;
public:
    explicit CodeContext(AVCodec* codec);

    AVCodecContext *get();

    int getHeight();

    int getWidth();

    int getPixFmt();

    ~CodeContext();
};


#endif //MICROMACHINES_CODECONTEXT_H
