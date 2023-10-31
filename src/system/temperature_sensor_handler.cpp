#include "temperature_sensor_handler.h"
#include "control_task_scheduler.h"
#include "mqtt_client.h"
#include "application.h"
#include <iomanip>
#include <sstream>

extern Application app;

TemperatureSensorHandler::TemperatureSensorHandler()
{
    _wire = new OneWire(ONE_WIRE_BUS);
    _sensors = new DallasTemperature(_wire);
}

std::string TemperatureSensorHandler::addressToString(DeviceAddress deviceAddress)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < 8; i++)
    {
        ss << std::setw(2) << static_cast<unsigned>(deviceAddress[i]);
    }
    return ss.str();
}

void TemperatureSensorHandler::init()
{
    _sensors->begin();
    int numberOfDevices = _sensors->getDeviceCount();

    for (int i = 0; i < numberOfDevices; i++)
    {
        // get device address an output via gui
        DeviceAddress deviceAddress;
        _sensors->getAddress(deviceAddress, i);
        std::string address = addressToString(deviceAddress);

        // create senor entity
        // This function should later assign the IDs correctly from EEPROM data
        sensors_entities.push_back(new TemperatureEntity("temp" + std::to_string(i + 1), i, this));

        app.getGui().addMessage({"Temperature" + std::to_string(i) + ": ", MessageType::INFO, address, 2000});
        Serial.print("\nTemperature Sensor Address:");
        Serial.println(address.c_str());
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