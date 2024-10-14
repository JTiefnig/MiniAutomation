#ifndef BINARY_OUTPUT_H
#define BINARY_OUTPUT_H

#include <Arduino.h>
#include "entity_base.h"
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
    OutEntity(std::string name, int pin, BinaryOutputHandler *sr, MqttClient *client);
    ~OutEntity();

    void set(State state);

    bool processMessage(const MqttMsg &msg) override;

    virtual MqttMsg toMessage() const override;

    State get() const;
};

#endif // !BINARY_OUTPUT_H