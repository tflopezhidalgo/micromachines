#ifndef MICROMACHINES_SDLWRAPPER_H
#define MICROMACHINES_SDLWRAPPER_H

#include "../common/Thread.h"

class SDLWrapper: public Thread{
    public:
        SDLWrapper();
        void run() override;
        ~SDLWrapper();
};
#endif
