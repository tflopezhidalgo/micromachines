#include "OutputFormat.h"

#define ERROR_FORMAT "No output format found\n"
#define INIT_CODEC "Codec can't be initialized\n"

OutputFormat::OutputFormat(const std::string& filename) {
    // Intenta deducir formato según extensión
    this->avOutputFormat = av_guess_format(NULL, filename.c_str(), NULL);
    if (!this->avOutputFormat) {
        // Intenta usar el formato standard
        this->avOutputFormat = av_guess_format("mpeg", NULL, NULL);
    }
    if (!this->avOutputFormat) {
        throw OutputFormatException(ERROR_FORMAT);
    }
    this->avOutputFormat->video_codec = AV_CODEC_ID_H264;

    AVCodec *codec = avcodec_find_encoder(this->avOutputFormat->video_codec);
    if (!codec) {
        throw OutputFormatException(INIT_CODEC);
    }
    //codecContextInit(codec);
    //this->outputFile = fopen(filename.c_str(), "wb");
}

OutputFormat::~OutputFormat() {

}

AVCodec *OutputFormat::getCodec() {
    return this->codec;
}

