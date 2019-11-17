#include "Frame.h"

#define ERROR_FRAME ""

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
    // write
}

AVFrame *Frame::get() {
    return this->frame;
}

Frame::~Frame() {
    av_frame_free(&frame);
}
