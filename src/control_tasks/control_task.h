#ifndef CONTROL_TASK_H
#define CONTROL_TASK_H

#include "control_task_base.h"
#include <functional>

class ControlTask : public ControlTaskBase
{
private:
    /* data */
    std::function<void()> task;

public:
    ControlTask(std::function<void()> task, uint16_t interval);
    ~ControlTask();

    void execute() override;
};

#endif