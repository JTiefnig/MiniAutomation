#ifndef MQTT_ENTITY_H
#define MQTT_ENTITY_H
#include <string>
#include "mqtt_interface.h"
#include "entity_base.h"
#include "mqtt_message.h"

class MqttEntity : public EntityBase, public MqttInterface
{

public:
    MqttEntity(std::string name, MqttInterface &client) : EntityBase(name),
                                                          MqttInterface(client)
    {
    }
    virtual ~MqttEntity() {}

    virtual bool processMessage(MqttMsg &msg) override = 0;

    virtual MqttMsg toMessage() const = 0;

    virtual std::string getTopic() override
    {
        return getName();
    }

    virtual void publishState() override
    {
        MqttMsg msg = toMessage();
        pushMessage(msg);
    }
};

#endif