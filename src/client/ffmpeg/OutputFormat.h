#ifndef MICROMACHINES_OUTPUTFORMAT_H
#define MICROMACHINES_OUTPUTFORMAT_H

#include "FormatContext.h"
#include "RecorderException.h"

extern "C" {
#include <libavutil/opt.h>
}

class OutputFormat {
private:
    AVOutputFormat* avOutputFormat;
    AVCodec *codec;
    FILE* outputFile;
public:
    explicit OutputFormat(const std::string& filename);

    AVCodec *getCodec();

    ~OutputFormat();
};


#endif //MICROMACHINES_OUTPUTFORMAT_H
