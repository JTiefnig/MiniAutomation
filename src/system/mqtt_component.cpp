#include "mqtt_component.h"
#include "mqtt_client.h"

MqttComponent::MqttComponent(MqttClient *client) : client(client)
{
    client->addComponent(this);
}
MqttComponent::~MqttComponent()
{
    client->removeComponent(this);
}

void MqttComponent::publishState() const
{
    client->publish(toMessage());
}