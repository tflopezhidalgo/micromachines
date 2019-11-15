//
// Created by leobellaera on 13/11/19.
//

#include <iostream>
#include "Example.h"

void Example::updateModel() {
    std::cout<<"Working\n";
}

extern "C" Plugin* create() {
    return new Example;
}
