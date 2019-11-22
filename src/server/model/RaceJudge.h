#ifndef MICROMACHINES_RACEJUDGE_H
#define MICROMACHINES_RACEJUDGE_H


#include <unordered_map>
#include "Car.h"

class RaceJudge {
private:
    int raceLaps;
    int checkpointsNumber;
    std::vector<std::string> arrivalOrder;
    std::unordered_map<std::string, int> checkpointsTaken;
    std::unordered_map<std::string, int> nextCheckpoint;
    std::unordered_map<std::string, int> lapsDone;
public:
    RaceJudge(int raceLaps);

    void addCar(std::string& id);

    void increaseCheckpointsNumber();

    void activate(std::string carId, int checkpointOrder);

    bool raceFinished();

    int getLapsDone(std::string& carId);

    int getCheckpointsTaken(std::string& carId);

    std::vector<std::string>& getCarsArrivalOrder();

    ~RaceJudge();
};


#endif //MICROMACHINES_RACEJUDGE_H
