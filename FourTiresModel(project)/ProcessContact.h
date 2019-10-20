//
// Created by eliana on 19/10/19.
//

#ifndef TESTING_PROCESSCONTACT_H
#define TESTING_PROCESSCONTACT_H

#include "Box2D/Box2D.h"
#include "CrashObject.h"
#include "Car.h"

class ProcessContact : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact) override;

    void crash(CrashObject &object1, CrashObject &object2);
};

#endif //TESTING_PROCESSCONTACT_H
