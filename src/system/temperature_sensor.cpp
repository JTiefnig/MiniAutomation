#include "temperature_sensor.h"
#include "helpers.h"

void TemperatureEntity::process(const std::string message)
{
    // do nothing
}

TemperatureEntity::TemperatureEntity(std::string name, uint8_t id, TemperatureSensorHandler *sensors, MqttClient *client)
    : EntityBase(name), id(id), sensors(sensors), MqttComponent(client)
{
}

TemperatureEntity::~TemperatureEntity() {} // Temeratur Entity does not respond to MQTT messages

float TemperatureEntity::get() const
{
    float temperatureC = sensors->getTempCByIndex(id);
    return temperatureC;
}

bool TemperatureEntity::processMessage(const MqttMsg &msg)
{
    return false;
}

MqttMsg TemperatureEntity::toMessage() const
{
    std::string stateTopic = client->getDeviceId() + "/" + this->name;
    float temperatureReading = get();
    std::string temperatureReadingStr = std::to_string(temperatureReading);
    return MqttMsg(stateTopic, temperatureReadingStr);
}