#ifndef MICROMACHINES_FORMATCONTEXT_H
#define MICROMACHINES_FORMATCONTEXT_H

extern "C" {
#include <libavformat/avformat.h>
}


class FormatContext {
private:
    AVFormatContext *pFormatCtx;
public:
    FormatContext();

    AVFormatContext* getContext() const;

    ~FormatContext();
};


#endif //MICROMACHINES_FORMATCONTEXT_H
