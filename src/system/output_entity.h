#include <Arduino.h>
#include "entity.h"
#include "config.h"
#include "mqtt_component.h"
#include <string>
#include <ShiftRegister74HC595.h>
#include "application.h"

// parameters: <number of shift registers> (data pin, clock pin, latch pin)
// refactor incapsolate in entity handler class
ShiftRegister74HC595<NUM_SR> sr(PIN_SR_DATA, PIN_SR_CLOCK, PIN_SR_LATCH);

extern Application app;

class OutEntity : public EntityBase, public MqttComponent
{
public:
    enum State
    {
        ON = 0,
        OFF
    };

    // defnie state names as 2 const char pointers static
    static const char *stateNames[];

private:
    int pin;
    State state;

public:
    OutEntity(std::string name, int pin)
        : EntityBase(name), pin(pin)
    {
        app.getMqttClient().addComponent(this);
    }
    ~OutEntity()
    {
        app.getMqttClient().removeComponent(this);
    }

    void process(const std::string message)
    {
        if (message == stateNames[ON])
        {
            sr.set(pin, HIGH);
        }
        else if (message == stateNames[OFF])
        {
            sr.set(pin, LOW);
        }
    }

    void set(State state)
    {
        if (state != this->state)
        {
            this->state = state;
        }
        if (state == ON)
        {
            sr.set(pin, HIGH);
        }
        else if (state == OFF)
        {
            sr.set(pin, LOW);
        }
        publishState(app.getMqttClient());
    }

    void publishState(MQTTClient &client) override
    {
        std::string stateTopic = client.getDeviceId() + "/" + topic() + "/state";
        client.publish(new MQMessage(stateTopic, stateNames[state]));
    }

    bool processMessage(const MQMessage &msg) override
    {
        std::vector<std::string> tokens = msg.splitTopic();
        if (tokens.size() != 3)
            return false;

        if (tokens[1] == topic() && tokens[2] == "set")
        {
            if (msg.payload == stateNames[ON])
            {
                set(ON);
            }
            else if (msg.payload == stateNames[OFF])
            {
                set(OFF);
            }
            return true;
        }
        return false;
    }

    std::string topic() override
    {
        return this->getName();
    }

    State get()
    {
        return state;
    }
};

const char *OutEntity::stateNames[] = {"ON", "OFF"};