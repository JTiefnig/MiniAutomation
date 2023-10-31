#ifndef MQTT_MESSAGE_H
#define MQTT_MESSAGE_H
#include <string>
#include "pubsubclient.h"

struct MQMessageBase
{
    std::string topic;

    // todo: an itertor hat iterates over the topic

    MQMessageBase(const std::string topic) : topic(topic)
    {
    }

    virtual void publish(PubSubClient &client) = 0;

    std::vector<std::string> splitTopic() const
    {
        std::vector<std::string> result;
        std::string::size_type start = 0;
        std::string::size_type end = 0;
        while ((end = topic.find('/', start)) != std::string::npos)
        {
            result.push_back(topic.substr(start, end - start));
            start = end + 1;
        }
        result.push_back(topic.substr(start));
        return result;
    }
};

struct MQMessage : MQMessageBase
{
    std::string payload;

    MQMessage(const std::string topic, const std::string payload) : MQMessageBase(topic), payload(payload)
    {
    }

    virtual void publish(PubSubClient &client)
    {
        client.publish(topic.c_str(), payload.c_str());
    }
};

struct ByteMQMessage : MQMessageBase
{
    uint8_t *payload;
    size_t length;

    ByteMQMessage(const std::string topic, uint8_t *payload, size_t length)
        : MQMessageBase(topic)
    {
        // clone payload in heap
        this->payload = new uint8_t[length];
        memcpy(this->payload, payload, length);
        this->length = length;
    }

    virtual void publish(PubSubClient &client)
    {
        client.publish(topic.c_str(), payload, length);
    }
};

#endif //