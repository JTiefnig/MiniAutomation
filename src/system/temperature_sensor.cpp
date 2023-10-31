#include "temperature_sensor.h"

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
    float temperature = get();

    // client.publish(mqtt_topic, (const uint8_t *)&temperature, sizeof(temperature));

    client.publish(new ByteMQMessage(this->name, (byte *)&temperature, sizeof(temperature)));
}

std::string TemperatureEntity::topic()
{
    return this->name;
}

bool TemperatureEntity::processMessage(const MQMessage &msg)
{
    return false;
}

void TemperatureEntity::publishState(MQTTClient &client)
{
    std::string stateTopic = client.getDeviceId() + "/" + topic() + "/state";
    float temperatureReading = get();
    client.publish(new ByteMQMessage(stateTopic, (byte *)&temperatureReading, sizeof(temperatureReading)));
}