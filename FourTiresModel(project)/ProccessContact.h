//
// Created by eliana on 19/10/19.
//

#ifndef TESTING_PROCCESSCONTACT_H
#define TESTING_PROCCESSCONTACT_H

#include "Box2D/Box2D.h"
#include "CrashObject.h"
#include "Car.h"

class ProccessContact : public b2ContactListener {
public:
    void BeginContact(b2Contact* contacto);

    void crash(CrashObject &object1, CrashObject &object2);
};


#endif //TESTING_PROCCESSCONTACT_H
