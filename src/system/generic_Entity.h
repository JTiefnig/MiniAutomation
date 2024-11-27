#ifndef GENERIC_ENTITY_H
#define GENERIC_ENTITY_H
#include <iostream>
#include <sstream>
#include <string>
#include "mqtt_client.h"
#include "mqtt_message.h"
#include "mqtt_entity.h"

template <typename T>
class GenericEntity : public MqttEntity
{

public:
    GenericEntity(const std::string name, const T &value, MqttInterface &mqtt_interface) : MqttEntity(name, mqtt_interface), value(value)
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
        publishState();
    }

    virtual bool processMessage(MqttMsg &msg) override
    {
        std::vector<std::string> tokens = msg.getTopicPath();
        if (tokens.size() != 2)
            return false;

        if (tokens[0] == this->getTopic() && tokens[1] == "set")
        {
            fromPayload(msg.getPayload());
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
        return MqttMsg(toPayload());
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