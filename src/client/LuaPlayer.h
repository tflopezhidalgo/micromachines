#ifndef MICROMACHINES_LUAPLAYER_H
#define MICROMACHINES_LUAPLAYER_H

#include "ProtectedModel.h"
#include "ProtectedQueue.h"
#include "Event.h"
#include "lua/LuaScript.h"
#include "Thread.h"

class LuaPlayer : public Thread{
private:
    ProtectedQueue<Event>& q;
    ProtectedModel& model;
    LuaScript script;
    bool alive;

public:
    LuaPlayer(ProtectedQueue<Event>& q, ProtectedModel& model,
            std::string playerId, std::string scriptFile);
    void run();
    void stop();
    ~LuaPlayer() {}
};
#endif
