//
// Created by leobellaera on 4/11/19.
//

#ifndef MICROMACHINES_RACEJUDGE_H
#define MICROMACHINES_RACEJUDGE_H


#include <unordered_map>
#include <entities/Car.h>

class Checkpoint;

class RaceJudge {
private:
    int raceLaps;
    std::vector<Checkpoint*> checkpoints;
    std::unordered_map<std::string, int> carsCheckpointsTaken;
    std::unordered_map<std::string, int> carsNextCheckpoint;
    std::string winnerId;
    bool someoneWon;
public:
    RaceJudge(int raceLaps);
    void addCar(std::string& id);
    void addCheckpoint(Checkpoint* checkpoint);
    void activate(std::string carId, int checkpointOrder);
    bool raceFinished();
    //todo getRacePositions
    ~RaceJudge();
};


#endif //MICROMACHINES_RACEJUDGE_H
