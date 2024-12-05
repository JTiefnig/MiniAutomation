#include "temperature_sensor_handler.h"
#include "control_task_scheduler.h"
#include "mqtt_client.h"
#include "application.h"
#include <iomanip>
#include <sstream>
#include <Preferences.h>

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

    Application &app = Application::inst();

    Preferences preferences;
    preferences.begin("tempSensors", false);
    for (int i = 0; i < numberOfDevices; i++)
    {
        // get device address an output via gui
        DeviceAddress deviceAddress;
        _sensors->getAddress(deviceAddress, i);
        std::string address = addressToString(deviceAddress);

        std::string name = preferences.getString("client_id").c_str();

        if (name == "")
        {
            name = "temp" + std::to_string(i + 1);
        }

        // create senor entity
        // This function should later assign the IDs correctly from EEPROM data
        sensors_entities.push_back(new TemperatureEntity(name, i, this, &Application::inst()));

        Serial.printf("\nTempSensor %i: ", i);
        Serial.println(address.c_str());
    }
    preferences.end();
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
    for (auto sensor : sensors_entities)
    {
        delete sensor;
    }
    sensors_entities.clear();
    delete _sensors;
    // delete all entities
}
