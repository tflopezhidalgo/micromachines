#include <zconf.h>
#include "Dispatcher.h"
#include "../common/Proxy.h"
#include "../common/Event.h"

Dispatcher::Dispatcher(ProtectedQueue<Event> &q, Proxy& proxy) :
    q(q), alive(true), proxy(proxy) {}

void Dispatcher::run() {
    while (alive) {
        try {
            Event action(std::move(q.pop()));
            std::string dumpedAction(std::move(action.serialize()));
            if (action.getActions()[0] == 'Q') {
                break;
            }

            proxy.sendMessage(dumpedAction);
        } catch (std::runtime_error &e) {
            std::cout << "Catcheo except en dispatcher\n";
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