#include "RaceJudge.h"

RaceJudge::RaceJudge(int raceLaps) :
    raceLaps(raceLaps),
    checkpointsNumber(0) {}

void RaceJudge::addCar(std::string& id) {
    nextCheckpoint.emplace(id, 0);
    checkpointsTaken.emplace(id, 0);
    lapsDone.emplace(id, 0);
}

void RaceJudge::increaseCheckpointsNumber() {
    checkpointsNumber++;
}

void RaceJudge::activate(std::string carId, int checkpointOrder) {

    if (std::find(arrivalOrder.begin(), arrivalOrder.end(), carId) != arrivalOrder.end()) {
        return;
    }

    auto nextCheckpointIt = nextCheckpoint.find(carId);
    auto checkpointsTakenIt = checkpointsTaken.find(carId);
    auto lapsDoneIt = lapsDone.find(carId);

    if (nextCheckpointIt->second == checkpointOrder) {
        checkpointsTakenIt->second += 1;
        nextCheckpointIt->second += 1;

        if (checkpointsTakenIt->second == (raceLaps * checkpointsNumber) + 1) {
            arrivalOrder.push_back(carId);
        }

        if (checkpointsTakenIt->second % (checkpointsNumber + 1) == 0) {
            lapsDoneIt->second += 1;
        }

        if (nextCheckpointIt->second == checkpointsNumber) {
            nextCheckpointIt->second = 0;
        }
    }

}

std::vector<std::string>& RaceJudge::getCarsArrivalOrder() {
    return arrivalOrder;
}

int RaceJudge::getLapsDone(std::string& carId) {
    return lapsDone.find(carId)->second;
}

int RaceJudge::getCheckpointsTaken(std::string& carId) {
    return checkpointsTaken.find(carId)->second;
}

bool RaceJudge::raceFinished() {
    //cars number is equal to the number of cars that finished the race
    return (arrivalOrder.size() == lapsDone.size());
}

RaceJudge::~RaceJudge() {}
