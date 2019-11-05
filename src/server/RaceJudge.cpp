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

void RaceJudge::addCheckpoint(Checkpoint* checkpoint) {
    checkpoints.push_back(checkpoint);
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

        if (checkpointsTakenIt->second == raceLaps * checkpoints.size()) {
            winnerId = carId;
            someoneWon = true;
            return;
        }

        if (nextCheckpointIt->second > checkpoints.size()) {
            nextCheckpointIt->second = 0;
        }
    }

}

bool RaceJudge::raceFinished() {
    return someoneWon;
}

RaceJudge::~RaceJudge() {
    for (int i = 0; i < checkpoints.size(); i++) {
        delete checkpoints[i];
    }
}
