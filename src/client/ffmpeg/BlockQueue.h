#ifndef MICROMACHINES_BLOCKQUEUE_H
#define MICROMACHINES_BLOCKQUEUE_H

#include "../Window.h"
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>


class BlockQueue {
private:
    std::queue <std::vector<char>> queue;
    std::mutex m;
    std::condition_variable cv_pop;
    bool _shutdown;
    Window& window;
public:
    BlockQueue();

    void push(std::vector<char> data);

    bool pop(std::vector<char> &data);

    void close();

    ~BlockQueue();
};


#endif //MICROMACHINES_BLOCKQUEUE_H
