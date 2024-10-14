#ifndef MQTT_MESSAGE_H
#define MQTT_MESSAGE_H
#include <string>
#include "pubsubclient.h"

struct MqttMsgBase
{
    std::string topic;
    // todo: an itertor hat iterates over the topic

    MqttMsgBase(const std::string topic) : topic(topic)
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

struct MqttMsg : MqttMsgBase
{
    std::string payload;

    MqttMsg(const std::string topic, const std::string payload) : MqttMsgBase(topic), payload(payload)
    {
    }

    virtual void publish(PubSubClient &client)
    {
        client.publish(topic.c_str(), payload.c_str());
    }
};

// TBD messages with other types of payloads

#endif //