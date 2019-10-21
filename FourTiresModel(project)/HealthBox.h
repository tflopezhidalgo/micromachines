//
// Created by eliana on 20/10/19.
//

#ifndef TESTING_HEALTHBOX_H
#define TESTING_HEALTHBOX_H

#include "CrashObject.h"

class HealthBox : public CrashObject {
private:
    b2Body* body;
    CrashType type;
    // Recuperan puntos de salud de los autos
public:
    HealthBox(b2World *world, b2Vec2 &pos);
    CrashType get_type();
    //b2Body* getBody() override;
    const b2Vec2 getPosition();
    //void startContact(CrashObject *object);
    //void endContact(CrashObject *object);
};


#endif //TESTING_HEALTHBOX_H
