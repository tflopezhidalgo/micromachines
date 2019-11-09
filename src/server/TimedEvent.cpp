//
// Created by leobellaera on 9/11/19.
//

#include "TimedEvent.h"

TimedEvent::TimedEvent(Runnable& cb, float timeout):
    elapsed(0),
    timeout(timeout),
    cb(cb) {}

TimedEvent::TimedEvent(TimedEvent &&other):
    cb(other.cb) {
    this->elapsed = other.elapsed;
    this->timeout = other.timeout;
}

bool TimedEvent::update(float delta) {
    elapsed += delta;
    if (elapsed >= timeout) {
        cb();
        return true;
    } else {
        return false;
    }
}

bool TimedEvent::operator<(const TimedEvent& timedEvent) {
    return (remainingTimeout() < timedEvent.remainingTimeout());
}

float TimedEvent::remainingTimeout() const {
    return timeout - elapsed;
}
