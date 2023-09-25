#ifndef CONTROL_TASK_H
#define CONTROL_TASK_H
#include <Arduino.h>
#include "../system/control_task_scheduler.h"

class ControlTask
{
    uint16_t interval;

public:
    ControlTask(uint16_t interval) : interval(interval) {}
    ~ControlTask();
    virtual void execute() = 0;

    uint16_t getExecutionInterval() const
    {
        return this->interval;
    }
};

#endif