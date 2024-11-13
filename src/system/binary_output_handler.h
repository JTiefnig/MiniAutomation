#ifndef BIN_OUTPUT_HANDLER_H
#define BIN_OUTPUT_HANDLER_H

#include <map>
#include <string>
#include <ShiftRegister74HC595.h>
#include "config.h"

class OutEntity;

class BinaryOutputHandler
{
private:
    // parameters: <number of shift registers> (data pin, clock pin, latch pin)
    // refactor incapsolate in entity handler class
    ShiftRegister74HC595<NUM_SR> sr;

    std::map<std::string, OutEntity *> entities;
    BinaryOutputHandler(/* args */);
    ~BinaryOutputHandler();

public:
    static BinaryOutputHandler &inst()
    {
        static BinaryOutputHandler instance;
        return instance;
    }

    void set(const uint8_t pin, const uint8_t value)
    {
        sr.set(pin, value);
    }

    OutEntity *CreateEntity(std::string name, uint8_t pin);
};
#endif // !BIN_OUTPUT_ENTITY_HANDLER_H
