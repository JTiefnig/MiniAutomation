#ifndef MQTT_COMPONENT_H
#define MQTT_COMPONENT_H

#include <string>
#include "mqtt_client.h"
#include "mqtt_message.h"

class MQTTClient;

class MqttComponent
{
protected:
    MQTTClient *client;

public:
    virtual std::string topic() const = 0;

    virtual bool processMessage(const MQMessage &msg) = 0;

    virtual void publishState() const = 0;

    MqttComponent(MQTTClient *client);
    ~MqttComponent();
};

#endif // MQTT_COMPONENT_H