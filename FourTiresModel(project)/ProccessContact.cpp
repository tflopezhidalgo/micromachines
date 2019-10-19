//
// Created by eliana on 19/10/19.
//

#include "ProccessContact.h"
#include "CrashObject.h"

// deberiamos tener una clase "chocable" para Borde, Car y RandomObjets
// cada una tiene su identificador, asi el casteo se hace sobre esa clase madre
// cuando se obtiene el user data, el objeto chocable se modifica

void ProccessContact::BeginContact(b2Contact *contacto) {
    CrashObject* crash1 = (CrashObject*)contacto->GetFixtureA()->GetBody()->GetUserData();
    CrashObject* crash2 = (CrashObject*)contacto->GetFixtureB()->GetBody()->GetUserData();

    if (crash1->getType() == CrashType::CAR) {
        switch (crash2->getType()) {
            case CrashType::CAR:
                // quitar puntos de vida, ambos autos
                // aplicar fuerza para que choque(? el auto tendra una shape.restitucion, maneja el choque
                //
                break;
            case CrashType::BORDER:
                // quitar vida(?
                break;
            case CrashType::BOX:
                // una caja golpea con menos fuerza que auto
                // quitar % vida auto
                break;
        }
    }
}