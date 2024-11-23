#include "binary_output.h"
#include "binary_output_handler.h"
#include "mqtt_interface.h"

OutEntity::OutEntity(std::string name, int pin, BinaryOutputHandler *sr, MqttInterface &client, State init_state)
    : MqttEntity(name, client), pin(pin), sr(sr), state(init_state)
{
}
OutEntity::~OutEntity()
{
}

void OutEntity::set(State setState)
{
    if (setState == this->state)
        return;

    this->state = setState;

    if (setState == ON)
    {
        sr->set(pin, HIGH);
    }
    else if (setState == OFF)
    {
        sr->set(pin, LOW);
    }

    callCallbacks();
    publishState();
}

bool OutEntity::processMessage(MqttMsg &msg)
{
    std::vector<std::string> tokens = msg.splitTopic();

    if (tokens.size() != 3)
        return false;

    if (tokens[1] == this->name && tokens[2] == "set")
    {
        if (msg.payload == stateNames[ON])
        {
            set(State::ON);
        }
        else if (msg.payload == stateNames[OFF])
        {
            set(State::OFF);
        }
        return true;
    }
    return false;
}

OutEntity::State OutEntity::get() const
{
    return state;
}

MqttMsg OutEntity::toMessage() const
{
    return MqttMsg(this->name, stateNames[state]);
}

const char *OutEntity::stateNames[] = {"ON", "OFF"};