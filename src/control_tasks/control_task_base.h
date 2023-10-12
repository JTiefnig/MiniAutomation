#ifndef CONTROL_TASK_BASE_H
#define CONTROL_TASK_BASE_H
#include <Arduino.h>
#include <functional>

class ControlTaskBase
{
    uint16_t interval;

public:
    ControlTaskBase(uint16_t interval) : interval(interval) {}
    ~ControlTaskBase() {}
    virtual void execute() = 0;

    uint16_t getExecutionInterval();
};

#endif