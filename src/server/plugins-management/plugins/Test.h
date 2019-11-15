//
// Created by leobellaera on 15/11/19.
//

#ifndef MICROMACHINES_TEST_H
#define MICROMACHINES_TEST_H


#include "../Plugin.h"

class Test : public Plugin {
public:
    void updateModel(std::unordered_map<std::string, Car*>& cars) override;
};


#endif //MICROMACHINES_TEST_H
