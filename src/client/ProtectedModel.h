#ifndef MICROMACHINES_PROTECTEDMODEL_H
#define MICROMACHINES_PROTECTEDMODEL_H

#include <mutex>
#include <vector>

class ProtectedModel {
private:
    std::mutex m;
    std::vector<<std::reference_wrapper<Entities>> entities;

public:
    




};

#endif
