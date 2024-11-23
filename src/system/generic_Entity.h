#ifndef GENERIC_ENTITY_H
#define GENERIC_ENTITY_H
#include <iostream>
#include <sstream>
#include <string>
#include "mqtt_client.h"
#include "mqtt_message.h"
#include "mqtt_interface.h"
#include "entity_base.h"

template <typename T>
class GenericEntity : public EntityBase, public MqttInterface
{
public:
    GenericEntity(const std::string name, const T &value, MqttClient *client)
        : EntityBase(name), value(value), MqttInterface(client)
    {
    }

    T get() const
    {
        return value;
    }

    void set(const T &newValue)
    {
        if (value == newValue)
            return;
        value = newValue;
        callCallbacks();
    }

    bool processMessage(const MqttMsg &msg) override
    {
        std::vector<std::string> tokens = msg.splitTopic();
        if (tokens.size() != 3)
            return false;

        if (tokens[1] == this->name && tokens[2] == "set")
        {
            fromPayload(msg.payload);
            return true;
        }
        return false;
    }

    operator T() const
    {
        return value;
    }

    GenericEntity<T> &operator=(const T &newValue)
    {
        this->set(newValue);
        return *this;
    }

    GenericEntity<T> &operator=(const GenericEntity<T> &other)
    {
        this->set(other.get());
        return *this;
    }

    bool operator==(const T &other) const
    {
        return this->get() == other;
    }

    virtual MqttMsg toMessage() const override
    {
        return MqttMsg(this->topic(), toPayload());
    }

private:
    std::string toPayload() const
    {
        // Transform the value to a string payload
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
    void fromPayload(const std::string &payload)
    {
        // Transform the payload to the value
        std::istringstream iss(payload);
        iss >> value;
    }

    std::string name;
    T value;
};

#endif // GENERIC_ENTITY_H