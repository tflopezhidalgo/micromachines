#ifndef MICROMACHINES_PROTECTEDVECTOR_H
#define MICROMACHINES_PROTECTEDVECTOR_H

#include "../Window.h"
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>


class ProtectedVector {
private:
    std::queue <std::vector<char>> queue;
    std::mutex m;
    std::condition_variable cv_pop;
    bool _shutdown;

public:
    ProtectedVector();

    void push(std::vector<char>& data);

    bool pop(std::vector<char> &data);

    void close();

    ~ProtectedVector();
};


#endif
