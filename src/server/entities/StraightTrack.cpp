//
// Created by leobellaera on 31/10/19.
//

#include "StraightTrack.h"

StraightTrack::StraightTrack(b2Body* body) :
    Entity(TRACK, body) {}

void StraightTrack::beginCollision(Entity* entity) {
    //todo
}

void StraightTrack::endCollision(Entity* entity) {

}

StraightTrack::~StraightTrack() {

}
