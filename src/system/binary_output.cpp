#include "binary_output.h"
#include "binary_output_hander.h"

OutEntity::OutEntity(std::string name, int pin, BinaryOutputHandler *sr, MQTTClient *client)
    : EntityBase(name), pin(pin), sr(sr), MqttComponent(client), state(OFF)
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

    this->callbacks.call();
    publishState();
}

void OutEntity::publishState() const
{
    std::string stateTopic = client->getDeviceId() + "/" + topic() + "/state";
    client->publish(new MQMessage(stateTopic, stateNames[state]));
}

bool OutEntity::processMessage(const MQMessage &msg)
{
    std::vector<std::string> tokens = msg.splitTopic();

    if (tokens.size() != 3)
        return false;

    if (tokens[1] == topic() && tokens[2] == "set")
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

std::string OutEntity::topic() const
{
    return this->getName();
}

OutEntity::State OutEntity::get() const
{
    return state;
}

const char *OutEntity::stateNames[] = {"ON", "OFF"};