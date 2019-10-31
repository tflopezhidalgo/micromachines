#include "Dispatcher.h"
#include "../common/Proxy.h"

Dispatcher::Dispatcher(ProtectedQueue<Action> &q, Proxy& proxy) :
    q(q), alive(true), proxy(proxy) {}

void Dispatcher::run() {
    while (alive) {
        Action action(std::move(q.pop()));
        std::string dumpedAction(std::move(action.dump()));
        proxy.sendMessage(dumpedAction);
        dumpedAction.clear();
    }
}

void Dispatcher::stop() {
    this->alive = false;
}
