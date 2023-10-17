#ifndef MQTT_MESSAGE_H
#define MQTT_MESSAGE_H
#include <string>

struct MQMessage
{
    std::string topic;
    std::string message;

    // todo: an itertor hat iterates over te topic

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

#endif //