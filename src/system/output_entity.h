#include "entity.h"
#include <string>
#include <ShiftRegister74HC595.h>

// parameters: <number of shift registers> (data pin, clock pin, latch pin)
ShiftRegister74HC595<2> sr(19, 15, 5); // Put this in main file

template <int N>
class OutEntity : public EntityBase
{
public:
    enum State
    {
        ON,
        OFF
    };

private:
    int pin;
    State state;
    ShiftRegister74HC595<N> &sr;

public:
    OutEntity(std::string name, int pin)
        : EntityBase(name), pin(pin)
    {
    }
    ~OutEntity() {}

    void process(const std::string message)
    {
        if (message == "ON")
        {
            sr.set(pin, HIGH);
        }
        else if (message == "OFF")
        {
            sr.set(pin, LOW);
        }
    }

    void set(State state)
    {
        this->state = state;
    }

    State get()
    {
        return state;
    }
};
