#ifndef BINARY_OUTPUT_H
#define BINARY_OUTPUT_H

#include "binary_output_handler.h"
#include "mqtt_entity.h"
#include "mqtt_message.h"

class BinaryOutputHandler;

class OutEntity : public MqttEntity
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
    OutEntity(std::string name, int pin, BinaryOutputHandler *sr, MqttInterface *client, State init_state = OFF);
    virtual ~OutEntity();

    void set(State state);

    bool processMessage(MqttMsg &msg) override;

    MqttMsg toMessage() const override;

    State get() const;
};

#endif // !BINARY_OUTPUT_H