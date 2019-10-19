//
// Created by eliana on 19/10/19.
//

#ifndef TESTING_PROCCESSCONTACT_H
#define TESTING_PROCCESSCONTACT_H

#include "Box2D/Box2D.h"
#include "Car.h"

class ProccessContact : public b2ContactListener {
public:
    void BeginContact(b2Contact* contacto);

    void InContact();

    void EndContact();
};


#endif //TESTING_PROCCESSCONTACT_H
