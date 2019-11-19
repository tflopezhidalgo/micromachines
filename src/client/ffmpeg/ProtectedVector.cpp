#include "ProtectedVector.h"

ProtectedVector::ProtectedVector() :
    _shutdown(false),
    full(false) {}

void ProtectedVector::push(std::vector<char>& data) {
    std::unique_lock<std::mutex> lock(m);
    actualFrame.swap(data);
    cv_pop.notify_all();
    full = true;
}

void ProtectedVector::close() {
    _shutdown = true;
    cv_pop.notify_all();
}

bool ProtectedVector::pop(std::vector<char> &data) {
    std::unique_lock<std::mutex> lock(m);
    while(!_shutdown && actualFrame.empty()) {
        cv_pop.wait(lock);
    }
    if (_shutdown) { return false; }
    data.swap(actualFrame);
    return true;
}

ProtectedVector::~ProtectedVector() = default;
