#include "temperature_sensor.h"
#include "helpers.h"

TemperatureEntity::TemperatureEntity(std::string name, uint8_t id, TemperatureSensorHandler *sensors, MqttInterface &client)
    : MqttEntity(name, client), id(id), sensors(sensors)
{
}

TemperatureEntity::~TemperatureEntity() {} // Temeratur Entity does not respond to MQTT messages

float TemperatureEntity::get() const
{
    float temperatureC = sensors->getTempCByIndex(id);
    return temperatureC;
}

bool TemperatureEntity::processMessage(MqttMsg &msg)
{
    return false;
}

MqttMsg TemperatureEntity::toMessage() const
{
    float temperatureReading = get();
    std::string temperatureReadingStr = std::to_string(temperatureReading);
    return MqttMsg(this->name, temperatureReadingStr);
}