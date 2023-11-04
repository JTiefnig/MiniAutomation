#ifndef BINARY_OUTPUT_H
#define BINARY_OUTPUT_H

#include <Arduino.h>
#include "entity.h"
#include "config.h"
#include "mqtt_component.h"
#include <string>
#include "application.h"
#include "mqtt_client.h"

class BinaryOutputHandler;

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
    const int pin;
    State state;
    BinaryOutputHandler *sr;

public:
    OutEntity(std::string name, int pin, BinaryOutputHandler *sr, MQTTClient *client);
    ~OutEntity();

    void set(State state);

    void publishState() const override;

    bool processMessage(const MQMessage &msg) override;

    std::string topic() const override;

    State get() const;
};

#endif // !BINARY_OUTPUT_H