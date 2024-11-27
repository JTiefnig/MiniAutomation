#pragma once

#include <vector>
#include <string>
#include "mqtt_client.h"
#include "mqtt_message.h"
#include "mqtt_entity.h"

class FixedStateEntity : public MqttEntity
{
private:
    int state;
    std::vector<std::string> stateNames;

public:
    FixedStateEntity(std::string name, MqttInterface &client, const std::vector<std::string> &stateNames, int state = 0)
        : MqttEntity(name, client), state(state), stateNames(stateNames)
    {
    }
    virtual ~FixedStateEntity() {}

    virtual bool processMessage(MqttMsg &msg) override
    {
        std::vector<std::string> tokens = msg.getTopicPath();
        if (tokens.size() != 2)
            return false;

        if (tokens[0] == this->getTopic() && tokens[1] == "set")
        {
            int newState = -1;
            for (int i = 0; i < stateNames.size(); i++)
            {
                if (msg.getPayload() == stateNames[i])
                {
                    newState = i;
                    break;
                }
            }
            if (newState != -1)
            {
                set(newState);
                return true;
            }
        }
        return false;
    }

    std::string getStateName() const
    {
        return stateNames[state];
    }

    int getState() const
    {
        return state;
    }

    void set(int newstate)
    {
        if (newstate < 0 || newstate >= stateNames.size())
        {
            return;
        }
        if (newstate != this->state)
        {
            this->state = newstate;
            publishState();
            callCallbacks();
        }
    }

    virtual MqttMsg toMessage() const override
    {
        MqttMsg msg(stateNames[state].c_str());
        return msg;
    }
};