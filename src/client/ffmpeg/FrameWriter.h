#ifndef MICROMACHINES_FRAMEWRITER_H
#define MICROMACHINES_FRAMEWRITER_H

#include "RecorderException.h"
#include "OutputFormat.h"
#include "CodecContext.h"
#include "Frame.h"
#include "Packet.h"
#include <string>
#include <cstdio>
#include <iostream>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}

class AVCodec;
class AVFrame;
class AVPacket;
class AVOutputFormat;
class AVStream;
class AVCodecContext;
class FormatContext;
class SwsContext;

class FrameWriter {
private:
    FormatContext& context;
    OutputFormat format;
    CodecContext codecContext;
    FILE* outFile;
    Frame frame;
    Packet packet;

public:
    FrameWriter(FormatContext &context, std::string &file, int width, int height);

    // cierra el stream de video
    void close();

    void write(const char* data);

    ~FrameWriter();
};


#endif //MICROMACHINES_FRAMEWRITER_H
