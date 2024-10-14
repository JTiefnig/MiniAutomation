#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include <string>
#include <sstream>
#include "mqtt_client.h"
#include "entity_base.h"
#include "temperature_sensor_handler.h"
#include "mqtt_component.h"

class TemperatureSensorHandler;

class TemperatureEntity : public EntityBase, public MqttComponent
{
private:
    uint8_t id;
    TemperatureSensorHandler *sensors;

public:
    virtual void process(const std::string message);

    TemperatureEntity(std::string name, uint8_t id, TemperatureSensorHandler *sensors, MqttClient *client);
    ~TemperatureEntity();

    virtual bool processMessage(const MqttMsg &msg) override;

    virtual MqttMsg toMessage() const override;

    float get() const;
};

#endif