#include "ProtectedVector.h"

ProtectedVector::ProtectedVector() : _shutdown(false) {}

void ProtectedVector::push(std::vector<char>& data) {
    std::unique_lock<std::mutex> lock(m);
    queue.push(std::move(data));
    cv_pop.notify_all();
}

void ProtectedVector::close() {
    _shutdown = true;
    cv_pop.notify_all();
}

bool ProtectedVector::pop(std::vector<char> &data) {
    std::unique_lock<std::mutex> lock(m);

    while(!_shutdown && queue.empty()) {
        cv_pop.wait(lock);
    }
    if (_shutdown) {
        return false;
    } else {
        data = std::move(queue.front());
        queue.pop();
        return true;
    }
}

ProtectedVector::~ProtectedVector() = default;
