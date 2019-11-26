#include <zconf.h>
#include "Dispatcher.h"
#include "../common/Proxy.h"
#include "../common/Event.h"
#include "Sound.h"
#include <vector>

Dispatcher::Dispatcher(ProtectedQueue<Event> &q, Proxy& proxy) :
    q(q), alive(true), proxy(proxy) {}

void Dispatcher::run() {
    while (alive) {
        try {
            Event action(std::move(q.pop()));
            if (action.getActions()[0] == 'Q') {
                break;
            }

            std::string dumpedAction(std::move(action.serialize()));
            proxy.sendMessage(dumpedAction);
        } catch (std::runtime_error &e) {
            stop();
        }
    }
}

void Dispatcher::stop() {
    proxy.stop();
    this->alive = false;
}

Dispatcher::~Dispatcher(){
    this->join();
}