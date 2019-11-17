#ifndef MICROMACHINES_SWSCONTEXTWRAPPER_H
#define MICROMACHINES_SWSCONTEXTWRAPPER_H

#include "BlockQueue.h"

extern "C" {
#include <libswscale/swscale.h>
}

class SwsContextWrapper {
private:
    BlockQueue &queue;
    int width;
    int height;
    SwsContext* swsContext;
    std::vector<char> data;
public:
    SwsContextWrapper(int width, int height);

    ~SwsContextWrapper();

    SwsContext *getContext();
};


#endif //MICROMACHINES_SWSCONTEXTWRAPPER_H
