#include <iostream>
#include "OutputFormat.h"

#define ERROR_FORMAT "No output format found\n"
#define INIT_CODEC "Codec can't be initialized\n"

OutputFormat::OutputFormat(const std::string& filename) {
    // Intenta deducir formato según extensión
    this->avOutputFormat = av_guess_format(NULL, filename.c_str(), NULL);
    std::cout << filename << std::endl;
    if (!this->avOutputFormat) {
        // Intenta usar el formato standard
        std::cout << "entre";
        this->avOutputFormat = av_guess_format("mpeg", NULL, NULL);
    }
    if (!this->avOutputFormat) {
        throw RecorderException(ERROR_FORMAT);
    }
    this->avOutputFormat->video_codec = AV_CODEC_ID_H264;

    this->codec = avcodec_find_encoder(this->avOutputFormat->video_codec);
    if (!codec) {
        throw RecorderException(INIT_CODEC);
    }
    //codecContextInit(codec);
    this->outputFile = fopen(filename.c_str(), "wb");
}

OutputFormat::~OutputFormat() {
    fclose(this->outputFile);
}

AVCodec *OutputFormat::getCodec() {
    return this->codec;
}

