#include "CollisionsProcessor.h"
#include "Entity.h"

void CollisionsProcessor::BeginContact(b2Contact* contact) {
    if (!contact || !contact->GetFixtureA() || !contact->GetFixtureB() ||
        !contact->GetFixtureA()->GetBody() || !contact->GetFixtureB()->GetBody()) {
        return;
    }
    void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    if (userDataA != nullptr && userDataB != nullptr) {
        auto entityA = static_cast<Entity*>(userDataA);
        auto entityB = static_cast<Entity*>(userDataB);
        entityA->beginCollision(entityB);
    }
}

void CollisionsProcessor::EndContact(b2Contact *contact) {
    if (!contact || !contact->GetFixtureA() || !contact->GetFixtureB() ||
        !contact->GetFixtureA()->GetBody() || !contact->GetFixtureB()->GetBody()) {
        return;
    }
    void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    if (userDataA != nullptr && userDataB != nullptr) {
        auto entityA = static_cast<Entity*>(userDataA);
        auto entityB = static_cast<Entity*>(userDataB);
        entityA->endCollision(entityB);
    }
}
