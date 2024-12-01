#include "mqtt_component.h"

MqttComponent::MqttComponent(MqttInterface *mqtt_int) : MqttInterface(mqtt_int)
{
}

MqttComponent::~MqttComponent()
{
}

bool MqttComponent::processMessage(MqttMsg &msg)
{
    if (msg.getTopicPath().empty())
        return false;

    if (msg.getTopicPath().front() != this->getTopic())
        return false;

    msg.popFirstTopic();

    return MqttInterface::processMessage(msg);
}

void MqttComponent::pushMessage(MqttMsg &msg)
{
    this->mqtt_int.pushMessage(msg.addTopicToken(this->getTopic()));
}
