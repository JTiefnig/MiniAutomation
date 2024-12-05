#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include <string>
#include <sstream>
#include "mqtt_entity.h"
#include "temperature_sensor_handler.h"
#include "mqtt_message.h"

class TemperatureSensorHandler;

class TemperatureEntity : public MqttEntity
{
private:
    uint8_t id;
    TemperatureSensorHandler *sensors;

public:
    TemperatureEntity(std::string name, uint8_t id, TemperatureSensorHandler *sensors, MqttInterface *interface);
    virtual ~TemperatureEntity();

    virtual bool processMessage(MqttMsg &msg);

    float get() const;

    virtual MqttMsg toMessage() const;
};

#endif