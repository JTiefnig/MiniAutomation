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
    OneWire *_wire;
    DallasTemperature *_sensors;
    std::vector<TemperatureEntity *> sensors_entities;

public:
    TemperatureSensorHandler();

    void init();

    float getTempCByIndex(uint8_t id) const;

    ~TemperatureSensorHandler();

    std::string addressToString(DeviceAddress deviceAddress);

    void setSensorName(uint8_t id, std::string name);

    std::vector<TemperatureEntity *> &getSensorsEntities()
    {
        return this->sensors_entities;
    }

    // copy construtor
};

#endif