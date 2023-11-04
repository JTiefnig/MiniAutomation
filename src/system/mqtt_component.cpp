#include "mqtt_component.h"
#include "mqtt_client.h"

MqttComponent::MqttComponent(MQTTClient *client) : client(client)
{
    client->addComponent(this);
}
MqttComponent::~MqttComponent()
{
    client->removeComponent(this);
}