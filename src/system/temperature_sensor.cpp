#include "temperature_sensor.h"
#include "helpers.h"

void TemperatureEntity::process(const std::string message)
{
    // do nothing
}

TemperatureEntity::TemperatureEntity(std::string name, uint8_t id, TemperatureSensorHandler *sensors, MQTTClient *client)
    : EntityBase(name), id(id), sensors(sensors), MqttComponent(client)
{
}

TemperatureEntity::~TemperatureEntity() {} // Temeratur Entity does not respond to MQTT messages

float TemperatureEntity::get() const
{
    float temperatureC = sensors->getTempCByIndex(id);
    return temperatureC;
}

void TemperatureEntity::publishState() const
{
    std::string stateTopic = client->getDeviceId() + "/" + this->topic();
    float temperatureReading = get();

    // std::ostringstream ss;
    // ss << temperatureReading;

    std::string temperatureReadingStr = std::to_string(temperatureReading);
    client->publish(new MQMessage(stateTopic, temperatureReadingStr));
}

std::string TemperatureEntity::topic() const
{
    return this->name;
}

bool TemperatureEntity::processMessage(const MQMessage &msg)
{
    return false;
}
