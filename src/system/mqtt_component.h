#pragma once
#include "mqtt_interface.h"
#include <string>

class MqttComponent : public MqttInterface
{

public:
    MqttComponent(MqttInterface *mqtt_int);
    virtual ~MqttComponent();

    bool processMessage(MqttMsg &msg) override;
    void pushMessage(MqttMsg &msg) override;

    virtual std::string getTopic() const = 0;
};