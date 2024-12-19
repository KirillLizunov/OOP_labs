#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <coroutine>
#include <deque>
#include <memory>
#include <functional>
#include "task.h"

class Task;

class Scheduler {
public:
    void schedule(Task&& task);
    void run();

    static Scheduler& instance();

private:
    std::deque<Task> tasks;
};

#endif