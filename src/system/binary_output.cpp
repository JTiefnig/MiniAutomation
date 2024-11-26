#include "binary_output.h"
#include "binary_output_handler.h"
#include "mqtt_interface.h"

OutEntity::OutEntity(std::string name, int pin, BinaryOutputHandler *sr, MqttInterface &client, State init_state)
    : MqttEntity(name, client), pin(pin), sr(sr), state(init_state)
{
    publishState();
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
    std::vector<std::string> tokens = msg.getTopicPath();

    if (tokens.size() != 2)
        return false;

    if (tokens[0] == this->getTopic() && tokens[1] == "set")
    {
        if (msg.getPayload() == stateNames[ON])
        {
            set(State::ON);
        }
        else if (msg.getPayload() == stateNames[OFF])
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
    return MqttMsg("state", stateNames[state]);
}

const char *OutEntity::stateNames[] = {"ON", "OFF"};