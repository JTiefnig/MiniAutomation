#ifndef BIN_OUTPUT_HANDLER_H
#define BIN_OUTPUT_HANDLER_H

#include <vector>
#include <ShiftRegister74HC595.h>
#include "config.h"

class OutEntity;

class BinaryOutputHandler
{
private:
    // parameters: <number of shift registers> (data pin, clock pin, latch pin)
    // refactor incapsolate in entity handler class
    ShiftRegister74HC595<NUM_SR> sr;

public:
    BinaryOutputHandler(/* args */);
    ~BinaryOutputHandler();

    void set(const uint8_t pin, const uint8_t value)
    {
        sr.set(pin, value);
    }
};

#endif // !BIN_OUTPUT_ENTITY_HANDLER_H
