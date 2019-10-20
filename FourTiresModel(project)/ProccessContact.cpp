//
// Created by eliana on 19/10/19.
//

#include "ProccessContact.h"
#include "CrashObject.h"

#define BOX_DAMAGE 20
#define CAR_DAMAGE 50

void ProccessContact::BeginContact(b2Contact *contacto) {
    if (CrashObject* crash1 = (CrashObject*)contacto->GetFixtureA()->GetBody()->GetUserData()) {
        if (CrashObject* crash2 = (CrashObject*)contacto->GetFixtureB()->GetBody()->GetUserData()) {
            crash(*crash2, *crash1);
            crash(*crash1, *crash2);
        }
    }
}

void ProccessContact::crash(CrashObject &object1, CrashObject &object2) {
    if (object1.getType() == CrashType::PLAYER) {
        switch (object2.getType()) {
            case CrashType::CAR:
                // quitar puntos de vida, ambos autos
                // aplicar fuerza para que choque(? el auto tendra una shape.restitucion, maneja el choque
                //object1.getDamage(CAR_DAMAGE);
                break;
            case CrashType::BORDER:
                // quitar vida(?
                // como es lo unico con lo que choco ahora le quito vida
                //object1.getDamage(BOX_DAMAGE);
                break;
            case CrashType::BOX:
                // una caja golpea con menos fuerza que auto
                // quitar % vida auto
                // premio o lo que sea
                break;
        }
    }
}
