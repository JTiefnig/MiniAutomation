
#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include <string>
#include <sstream>
#include "mqtt_client.h"
#include "entity.h"
#include "temperature_sensor_handler.h"

class TemperatureSensorHandler;

class TemperatureEntity : public EntityBase
{
private:
    uint8_t id;
    TemperatureSensorHandler *sensors;

public:
    virtual void process(const std::string message);

    TemperatureEntity(std::string name, uint8_t id, TemperatureSensorHandler *sensors);

    ~TemperatureEntity();

    std::string addressToString(DeviceAddress deviceAddress);

    float get() const;
    void publish(MQTTClient &client) const;
};

#endif