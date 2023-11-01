#include "temperature_sensor.h"
#include "helpers.h"

void TemperatureEntity::process(const std::string message)
{
    // do nothing
}

TemperatureEntity::TemperatureEntity(std::string name, uint8_t id, TemperatureSensorHandler *sensors)
    : EntityBase(name), id(id), sensors(sensors)
{
}

TemperatureEntity::~TemperatureEntity() {}

std::string TemperatureEntity::addressToString(DeviceAddress deviceAddress)
{
    std::ostringstream ss;
    // for (uint8_t i = 0; i < 8; i++)
    //     ss << std::setfill('0') << std::setw(2) << std::hex << (0xff & (unsigned int)deviceAddress[i]);
    return ss.str();
}

float TemperatureEntity::get() const
{
    float temperatureC = sensors->getTempCByIndex(id);
    return temperatureC;
}

void TemperatureEntity::publish(MQTTClient &client) const
{
    std::string stateTopic = client.getDeviceId() + "/" + this->topic();
    float temperatureReading = get();

    // std::ostringstream ss;
    // ss << temperatureReading;

    std::string temperatureReadingStr = std::to_string(temperatureReading);

    client.publish(new MQMessage(stateTopic, temperatureReadingStr));
}

std::string TemperatureEntity::topic() const
{
    return this->name;
}

bool TemperatureEntity::processMessage(const MQMessage &msg)
{
    return false;
}

void TemperatureEntity::publishState(MQTTClient &client)
{
    this->publish(client);
}