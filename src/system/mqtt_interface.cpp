#include "mqtt_interface.h"

MqttInterface::MqttInterface(MqttInterface &mqtt_int) : mqtt_int(mqtt_int)
{
    this->mqtt_int.addComponent(this);
}

MqttInterface::~MqttInterface()
{
    this->mqtt_int.removeComponent(this);
}

void MqttInterface::publishState()
{
    for (auto component : components)
    {
        component->publishState();
    }
}

bool MqttInterface::processMessage(MqttMsg &msg)
{
    // only one component can process the message
    for (auto component : components)
    {
        if (component->processMessage(msg))
        {
            return true;
        }
    }
    return false;
}

void MqttInterface::pushMessage(MqttMsg &msg)
{
    this->mqtt_int.pushMessage(msg);
}

void MqttInterface::addComponent(MqttInterface *component)
{
    components.push_back(component);
}

void MqttInterface::removeComponent(MqttInterface *component)
{
    components.erase(std::remove(components.begin(), components.end(), component), components.end());
}