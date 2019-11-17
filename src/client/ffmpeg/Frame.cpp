#include "Frame.h"

#define ERROR_FRAME "Error allocating memory for Frame\n"

Frame::Frame(int pix_fmt, int width, int height) :
    frame(av_frame_alloc()),
    currentPts(0) {
    if (!frame){
        throw RecorderException(ERROR_FRAME);
    }

    this->frame->format = pix_fmt;
    this->frame->width  = width;
    this->frame->height = height;

    av_frame_get_buffer(this->frame, 0);
}

AVFrame *Frame::get() {
    return this->frame;
}

void Frame::write(const char* bufferData, SwsContext *ctx) {
    const u_int8_t* data = (const u_int8_t*)bufferData;
    // El ancho del video x3 por la cantidad de bytes
    int width = this->frame->width * 3;

    sws_scale(ctx, &data, &width, 0, frame->height, frame->data, frame->linesize);

    this->frame->pts = currentPts;
    currentPts++;
}

Frame::~Frame() {
    av_frame_free(&frame);
}

