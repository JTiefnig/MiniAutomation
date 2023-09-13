#include "temperature_sensor_handler.h"

TemperatureSensorHandler::TemperatureSensorHandler()
{
    _wire = new OneWire(ONE_WIRE_BUS);
    _sensors = new DallasTemperature(_wire);
}

void TemperatureSensorHandler::init()
{
    _sensors->begin();
    int numberOfDevices = _sensors->getDeviceCount();

    std::vector<TemperatureEntity *> sensors_entities;

    for (int i = 0; i < numberOfDevices; i++)
    {
        // create senor entity
        // This function should later assign the IDs correctly from EEPROM data
        TemperatureEntity *tempSensor = new TemperatureEntity("temperature", i, this);
        sensors_entities.push_back(tempSensor);
    }
}

float TemperatureSensorHandler::getTempCByIndex(uint8_t id) const
{
    _sensors->requestTemperaturesByIndex(id);
    float temperatureC = _sensors->getTempCByIndex(id);
    return temperatureC;
}

TemperatureSensorHandler::~TemperatureSensorHandler()
{
    delete _wire;
    delete _sensors;
    // delete all entities
}