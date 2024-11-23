#pragma once

#include "control_task.h"
#include "../system/mqtt_interface.h"
#include "../system/mqtt_message.h"

class HeatingController : public ControlTaskBase, public MqttInterface
{
public:
    HeatingController(std::string name) : ControlTaskBase(1000), MqttInterface(name)
    {
    }

    ~HeatingController() {}

    void execute() override
    {
        switch (mode)
        {
        case HeatingMode::Temp:

            break;
        case HeatingMode::OFF:

            break;
        }
    }

    bool processMessage(const MqttMsg &msg) override
    {
        return false;
    }

    MqttMsg toMessage() const override
    {
        return MqttMsg("xx", "xx");
    }

    enum class HeatingMode
    {
        Temp,
        OFF
    };

    enum class HeatingState
    {
        ON,
        TURNING_OFF,
        OFF
    };

    void setMode(HeatingMode mode)
    {
        this->mode = mode;
    }

private:
    HeatingMode mode;
};