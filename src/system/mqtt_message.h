#ifndef MQTT_MESSAGE_H
#define MQTT_MESSAGE_H
#include <string>
#include "pubsubclient.h"
#include <utility>

struct MqttMsg
{
    std::string topic;
    // todo: an itertor hat iterates over the topic
    std::string payload;

    MqttMsg(const std::string topic, const std::string msg) : topic(topic), payload(msg)
    {
    }

    MqttMsg(const MqttMsg &msg) : topic(msg.topic), payload(msg.payload)
    {
    }

    MqttMsg(MqttMsg &&msg) noexcept : topic(std::move(msg.topic)), payload(std::move(msg.payload))
    {
    }

    void publish(PubSubClient &client)
    {
        client.publish(topic.c_str(), payload.c_str());
    }

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

struct BinaryOutputMsg : MqttMsg
{
    const uint8_t *payload;
    const uint8_t length;
};

// TBD messages with other types of payloads

#endif //