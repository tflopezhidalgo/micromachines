//
// Created by leobellaera on 6/11/19.
//

#ifndef MICROMACHINES_ENTITIESMANAGER_H
#define MICROMACHINES_ENTITIESMANAGER_H

#include <entities/Entity.h>
#include <entities/Projectile.h>
#include <unordered_map>
#include "World.h"

class EntitiesManager {
private:
    World* world;
    std::unordered_map<int, Projectile*> projectiles;
    std::unordered_map<int, Entity*> entities;
    int entitiesCounter;
public:
    EntitiesManager(World* stageWorld);
    void addProjectile(EntityIdentifier entityIdentifier, float x_pos, float y_pos, b2Vec2 impulse);
    void addEntity(EntityIdentifier entityIdentifier, float x_pos, float y_pos);
    void deleteDeadEntities();
    void updateProjectilesStatus();
    void updateProjectilesFriction();
    std::unordered_map<int, Entity*>& getEntities();
    ~EntitiesManager();

};


#endif //MICROMACHINES_ENTITIESMANAGER_H
