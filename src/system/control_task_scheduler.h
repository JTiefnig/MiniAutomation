#ifndef CONTROL_TASK_SCHEDULER_H
#define CONTROL_TASK_SCHEDULER_H

#include <Arduino.h>
#include <vector>
#include "config.h"
#include "../control_tasks/control_task.h"

class ControlTask;

class ControlTaskScheduler
{
private:
    // tasklist
    std::vector<ControlTask *> tasks;
    uint16_t hcfInterval = 1000; // default 1 sec
    uint16_t largestInterval = 0;
    uint64_t cycleTime = 0;

    unsigned long findHCF(unsigned long a, unsigned long b)
    {
        while (b != 0)
        {
            unsigned long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    void calculateHCF()
    {
        if (tasks.empty())
        {
            hcfInterval = 1000; // Default to 1 second if no tasks are present
            return;
        }

        // Initialize the HCF to the first task's interval
        hcfInterval = tasks[0]->getExecutionInterval();

        // Find the HCF of all task intervals
        for (const auto &task : tasks)
        {
            hcfInterval = findHCF(hcfInterval, task->getExecutionInterval());
        }
    }

public:
    ControlTaskScheduler(/* args */) {}
    ~ControlTaskScheduler()
    {
    }

    void addTask(ControlTask *task)
    {
        tasks.push_back(task);

        if (task->getExecutionInterval() > largestInterval)
        {
            largestInterval = task->getExecutionInterval();
        }
    }
    // members

    void loop()
    {

        for (auto task : this->tasks)
        {
            if (cycleTime % task->getExecutionInterval() == 0)
                task->execute();
        }

        cycleTime += hcfInterval;
        if (cycleTime >= largestInterval)
            cycleTime = 0;

        vTaskDelay(hcfInterval / portTICK_PERIOD_MS);
    }
};

#endif
