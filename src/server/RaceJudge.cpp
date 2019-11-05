//
// Created by leobellaera on 4/11/19.
//

#include "RaceJudge.h"

RaceJudge::RaceJudge(int raceLaps) :
    raceLaps(raceLaps),
    someoneWon(false) {}

void RaceJudge::addCar(std::string& id) {
    carsNextCheckpoint.emplace(id, 0);
    carsCheckpointsTaken.emplace(id, 0);
}

void RaceJudge::increaseCheckpointsNumber() {
    checkpointsNumber++;
}

void RaceJudge::activate(std::string carId, int checkpointOrder) {
    if (someoneWon) {
        return;
    }

    auto nextCheckpointIt = carsNextCheckpoint.find(carId);
    auto checkpointsTakenIt = carsCheckpointsTaken.find(carId);

    if (nextCheckpointIt->second == checkpointOrder) {
        checkpointsTakenIt->second += 1;
        nextCheckpointIt->second += 1;

        if (checkpointsTakenIt->second == raceLaps * checkpointsNumber) {
            winnerId = carId;
            someoneWon = true;
            return;
        }

        if (nextCheckpointIt->second > checkpointsNumber - 1) {
            nextCheckpointIt->second = 0;
        }
    }

}

bool RaceJudge::raceFinished() {
    return someoneWon;
}

RaceJudge::~RaceJudge() {}
