#ifndef MQTT_COMPONENT_H
#define MQTT_COMPONENT_H

#include <string>
#include "mqtt_client.h"
#include "mqtt_message.h"

class MqttClient;

class MqttComponent
{
protected:
    MqttClient *client;

public:
    virtual bool processMessage(const MqttMsg &msg) = 0;

    virtual MqttMsg toMessage() const = 0;

    virtual void publishState() const;

    MqttComponent(MqttClient *client);
    ~MqttComponent();
};

#endif // MQTT_COMPONENT_H