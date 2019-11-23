#include "ProtectedVector.h"
#include "RecorderException.h"

#define ERROR_NOT_EMPTY "Error not empty data"

ProtectedVector::ProtectedVector() :
    _shutdown(false) {}

void ProtectedVector::push(std::vector<char>& data) {
    std::unique_lock<std::mutex> lock(m);
    actualFrame.swap(data);
    cv_pop.notify_all();
}

void ProtectedVector::close() {
    _shutdown = true;
    cv_pop.notify_all();
}

bool ProtectedVector::pop(std::vector<char> &data) {
    if(!data.empty()) throw RecorderException(ERROR_NOT_EMPTY);

    std::unique_lock<std::mutex> lock(m);
    while(!_shutdown && actualFrame.empty()) {
        cv_pop.wait(lock);
    }
    if (_shutdown) { return false; }
    data.swap(actualFrame);
    return true;
}

ProtectedVector::~ProtectedVector() = default;
