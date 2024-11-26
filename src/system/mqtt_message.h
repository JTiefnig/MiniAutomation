#ifndef MQTT_MESSAGE_H
#define MQTT_MESSAGE_H
#include <string>
#include "pubsubclient.h"
#include <utility>
#include <vector>
#include <algorithm>

class MqttMsg
{
public:
    MqttMsg(const std::string topic, const std::string msg) : payload(msg)
    {
        splitTopic(topic);
    }

    MqttMsg(const MqttMsg &msg) : payload(msg.payload), topic_path(msg.topic_path)
    {
    }

    MqttMsg(MqttMsg &&msg) noexcept : topic_path(std::move(msg.topic_path)), payload(std::move(msg.payload))
    {
    }

    MqttMsg(const std::string msg) : payload(msg)
    {
    }

    void setTopic(std::string topic)
    {
    }

    void publish(PubSubClient &client)
    {
        client.publish(getTopic().c_str(), payload.c_str());
    }

    std::vector<std::string> getTopicPath() const
    {
        return topic_path;
    }

    std::string getTopic()
    {
        std::string topic;
        for (auto &t : topic_path)
        {
            topic += t;
            if (t != topic_path.back())
                topic += '/';
        }
        return topic;
    }

    MqttMsg &addTopicToken(const std::string &token)
    {
        // topic_path.push_back(token);
        topic_path.insert(topic_path.begin(), token);
        return *this;
    }

    std::string getPayload()
    {
        return payload;
    }

    MqttMsg &popFirstTopic()
    {
        if (!topic_path.empty())
        {
            topic_path.erase(topic_path.begin());
        }
        return *this;
    }

private:
    std::vector<std::string> topic_path;
    std::string payload;

    void splitTopic(std::string topic)
    {
        topic_path.clear();
        std::string::size_type start = 0;
        std::string::size_type end = 0;
        while ((end = topic.find('/', start)) != std::string::npos)
        {
            topic_path.push_back(topic.substr(start, end - start));
            start = end + 1;
        }
        topic_path.push_back(topic.substr(start));
    }
};

#endif //