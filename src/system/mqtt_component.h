#ifndef MQTT_COMPONENT_H
#define MQTT_COMPONENT_H

#include <string>
#include "mqtt_client.h"

class MQTTClient;
struct MqttInMessage;

class MqttComponent
{
protected:
    const MQTTClient &client;

public:
    virtual std::string topic() = 0;

    virtual bool processMessage(const MqttInMessage &msg) = 0;

    virtual void publishState() = 0;

    MqttComponent(const MQTTClient &client)
        : client(client)
    {
    }
    ~MqttComponent();
};

#endif // MQTT_COMPONENT_H