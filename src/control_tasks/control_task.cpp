#include "control_task.h"

ControlTask::ControlTask(std::function<void()> task, uint16_t interval) : ControlTaskBase(interval), task(task) {}
ControlTask::~ControlTask()
{
}

void ControlTask::execute()
{
    this->task();
}

uint16_t ControlTaskBase::getExecutionInterval()
{
    return this->interval;
}