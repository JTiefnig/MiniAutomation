#ifndef MQTT_COMPONENT_H
#define MQTT_COMPONENT_H

#include <string>
#include "mqtt_client.h"
#include "mqtt_message.h"

class MQTTClient;

class MqttComponent
{
public:
    virtual std::string topic() = 0;

    virtual bool processMessage(const MQMessage &msg) = 0;

    virtual void publishState(MQTTClient &client) = 0;

    MqttComponent();
    ~MqttComponent();
};

#endif // MQTT_COMPONENT_H