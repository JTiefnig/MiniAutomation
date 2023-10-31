#ifndef TEMPERATURE_SENSOR_HANDLER_H
#define TEMPERATURE_SENSOR_HANDLER_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include <string>
#include <sstream>
#include <vector>
#include "temperature_sensor.h"

class TemperatureEntity;

class TemperatureSensorHandler
{
private:
    int id;
    // std::vector<TemperatureEntity *> sensors_entities;
    OneWire *_wire;
    DallasTemperature *_sensors;
    std::vector<TemperatureEntity *> sensors_entities;

public:
    TemperatureSensorHandler();

    void init();

    float getTempCByIndex(uint8_t id) const;

    ~TemperatureSensorHandler();

    std::string addressToString(DeviceAddress deviceAddress);
};

#endif