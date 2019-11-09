//
// Created by leobellaera on 9/11/19.
//

#ifndef MICROMACHINES_TIMEDEVENT_H
#define MICROMACHINES_TIMEDEVENT_H

#include <functional>

class TimedEvent {
    typedef std::function<void ()> Runnable;
private:
    float timeout;
    float elapsed;
    Runnable& cb;
public:
    TimedEvent(Runnable& cb, float timeout);
    TimedEvent(TimedEvent &&other);
    bool update(float delta);
    float remainingTimeout() const;
    bool operator< (const TimedEvent& timedEvent);
};


#endif //MICROMACHINES_TIMEDEVENT_H
