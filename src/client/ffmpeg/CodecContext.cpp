#include "CodecContext.h"

#define ERROR_CODECCONTEXT "Error allocating memory for codeContext\n"

CodecContext::CodecContext(AVCodec *codec, int width, int height) :
    codecContext(avcodec_alloc_context3(codec)) {
    if (!codecContext) {
        throw RecorderException(ERROR_CODECCONTEXT);
    }

    // La resolución debe ser múltiplo de 2
    this->codecContext->width = width;
    this->codecContext->height = height;
    this->codecContext->time_base = {1,25};
    this->codecContext->framerate = {25,1};
    this->codecContext->pix_fmt = AV_PIX_FMT_YUV420P;
    this->codecContext->gop_size = 10;
    this->codecContext->max_b_frames = 2;
    if (codec->id == AV_CODEC_ID_H264) {
        this->codecContext->profile = FF_PROFILE_H264_BASELINE;
        av_opt_set(this->codecContext->priv_data, "preset", "slow", 0);
    }
    avcodec_open2(this->codecContext, codec, NULL);
}

int CodecContext::getHeight() {
    return this->codecContext->height;
}

int CodecContext::getPixFmt() {
    return this->codecContext->pix_fmt;
}

int CodecContext::getWidth() {
    return this->codecContext->width;
}

AVCodecContext *CodecContext::get() {
    return this->codecContext;
}

CodecContext::~CodecContext() {
    avcodec_close(this->codecContext);
    avcodec_free_context(&this->codecContext);
}
