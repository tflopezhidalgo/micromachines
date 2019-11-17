#ifndef MICROMACHINES_FRAMEWRITER_H
#define MICROMACHINES_FRAMEWRITER_H

#include "RecorderException.h"
#include "Frame.h"
#include "CodecContext.h"
#include "Packet.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}

class FrameWriter {
private:
    FormatContext& context;
    AVOutputFormat format;
    CodecContext codec;
    FILE* outFile;
    Frame frame;
    Packet packet;

public:
    void encode(CodecContext *codec, Frame *frame, Packet *packet, FILE *outFile);

    // cierra el stream de video
    void close();
};


#endif //MICROMACHINES_FRAMEWRITER_H
