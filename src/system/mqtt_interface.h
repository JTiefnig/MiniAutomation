#ifndef mqtt_interface_H
#define mqtt_interface_H

#include <string>
#include <vector>
#include "mqtt_message.h"

class MqttInterface
{
protected:
    MqttInterface *mqtt_int;
    std::vector<MqttInterface *> components;

public:
    MqttInterface() = default;
    MqttInterface(MqttInterface *mqtt_int);
    virtual ~MqttInterface();

    virtual bool processMessage(MqttMsg &msg);
    virtual void pushMessage(MqttMsg &msg);

    void addComponent(MqttInterface *component);
    void removeComponent(MqttInterface *component);

    virtual void publishState();
};

#endif // mqtt_interface_H