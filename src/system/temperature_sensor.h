#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include <string>
#include <sstream>
#include "mqtt_client.h"
#include "entity.h"
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

    TemperatureEntity(std::string name, uint8_t id, TemperatureSensorHandler *sensors, MQTTClient *client);
    ~TemperatureEntity();

    virtual std::string topic() const;

    virtual bool processMessage(const MQMessage &msg) override;

    virtual void publishState() const override;

    float get() const;
};

#endif