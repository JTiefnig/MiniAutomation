#ifndef SYSTEM_H
#define SYSTEM_H

#include <EEPROM.h>
#define EEPROM_SIZE 32

void EEPROM_TEST()
{
    EEPROM.begin(EEPROM_SIZE);
    int address = 0;
    int startcount = 0;
    startcount = EEPROM.read(address);
    startcount++;
    EEPROM.write(address, startcount);
    EEPROM.commit();
    EEPROM.end();
}

#include <Arduino.h>
#include <vector>

class OCOS_Task
{
public:
    OCOS_Task();
    ~OCOS_Task();
    virtual void execute() = 0;
};

class OpenControlOS
{
private:
    // tasklist
    std::vector<OCOS_Task *> taskList;

public:
    OpenControlOS(/* args */) {}
    ~OpenControlOS()
    {
    }

    OpenControlOS(OpenControlOS const &) = delete;
    void operator=(OpenControlOS const &) = delete;

    void addTask(OCOS_Task *task)
    {
        taskList.push_back(task);
    }
    // members

    void loop()
    {
        // loop over tasks and execute them in timeslot to do stuff
        for (auto task : this->taskList)
        {
            // to implement individual delay or timeslot for every task
            task->execute();
        }
    }
};

#endif
