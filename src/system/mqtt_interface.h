#ifndef mqtt_interface_H
#define mqtt_interface_H

#include <string>
#include <vector>
#include "mqtt_message.h"

class MqttInterface
{
protected:
    MqttInterface &mqtt_int;
    std::vector<MqttInterface *> components;

public:
    MqttInterface() = default;
    MqttInterface(MqttInterface &mqtt_int);
    virtual ~MqttInterface();

    virtual bool processMessage(MqttMsg &msg);
    virtual void pushMessage(MqttMsg &msg);
    virtual void publishState();

    void addComponent(MqttInterface *component);
    void removeComponent(MqttInterface *component);
};

#endif // mqtt_interface_H