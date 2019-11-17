#include "BlockQueue.h"

BlockQueue::BlockQueue() : _shutdown(false) {}

void BlockQueue::push(std::vector<char> data) {
    std::unique_lock<std::mutex> lock(m);
    queue.push(data);
    cv_pop.notify_all();
}

void BlockQueue::close() {
    _shutdown = true;
    cv_pop.notify_all();
}

bool BlockQueue::pop(std::vector<char> &data) {
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

BlockQueue::~BlockQueue() = default;
