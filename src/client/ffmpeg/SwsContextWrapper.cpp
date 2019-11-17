#include "SwsContextWrapper.h"

SwsContextWrapper::SwsContextWrapper(int width, int height) {

}

SwsContextWrapper::~SwsContextWrapper() {

}

SwsContext *SwsContextWrapper::getContext() {
    return this->swsContext;
}
