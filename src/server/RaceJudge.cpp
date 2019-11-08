//
// Created by leobellaera on 4/11/19.
//

#include "RaceJudge.h"

RaceJudge::RaceJudge(int raceLaps) :
    raceLaps(raceLaps),
    someoneWon(false) {}

void RaceJudge::addCar(std::string& id) {
    nextCheckpoint.emplace(id, 0);
    checkpointsTaken.emplace(id, 0);
    lapsDone.emplace(id, 0);
}

void RaceJudge::increaseCheckpointsNumber() {
    checkpointsNumber++;
}

void RaceJudge::activate(std::string carId, int checkpointOrder) {
    if (someoneWon) {
        return;
    }

    auto nextCheckpointIt = nextCheckpoint.find(carId);
    auto checkpointsTakenIt = checkpointsTaken.find(carId);
    auto lapsMadeIt = lapsDone.find(carId);

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
            lapsMadeIt->second += 1;
        }
    }

}

int RaceJudge::getLapsDone(std::string& carId) {
    return lapsDone.find(carId)->second;
}

std::string& RaceJudge::getWinnerId() {
    return winnerId;
}

bool RaceJudge::raceFinished() {
    return someoneWon;
}

RaceJudge::~RaceJudge() {}
