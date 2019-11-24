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
    std::unique_lock<std::mutex> lock(m);
    _shutdown = true;
    cv_pop.notify_all();
}

bool ProtectedVector::pop(std::vector<char> &data) {
    std::unique_lock<std::mutex> lock(m);
    if(!data.empty()) throw RecorderException(ERROR_NOT_EMPTY);
    while(!_shutdown && actualFrame.empty()) {
        cv_pop.wait(lock);
    }
    if (_shutdown) { return false; }
    data.swap(actualFrame);
    return true;
}

bool ProtectedVector::isClose() {
    std::unique_lock<std::mutex> lock(m);
    return _shutdown;
}

void ProtectedVector::open() {
    std::unique_lock<std::mutex> lock(m);
    _shutdown = false;
}

ProtectedVector::~ProtectedVector() = default;
