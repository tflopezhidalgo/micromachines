#ifndef MICROMACHINES_OUTPUTFORMAT_H
#define MICROMACHINES_OUTPUTFORMAT_H

#include "FormatContext.h"
#include "OutputFormatException.h"

class OutputFormat {
private:
    AVOutputFormat* avOutputFormat;
    AVCodec *codec;
public:
    explicit OutputFormat(const std::string& filename);

    AVCodec *getCodec();

    ~OutputFormat();
};


#endif //MICROMACHINES_OUTPUTFORMAT_H
