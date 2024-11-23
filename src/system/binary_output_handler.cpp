#include "binary_output_handler.h"
#include "config.h"
#include "application.h"
#include "binary_output.h"

BinaryOutputHandler::BinaryOutputHandler(/* args */) : sr(PIN_SR_DATA, PIN_SR_CLOCK, PIN_SR_LATCH)
{
}

BinaryOutputHandler::~BinaryOutputHandler()
{
}

OutEntity *BinaryOutputHandler::CreateEntity(std::string name, uint8_t pin)
{
    auto it = entities.find(name);
    if (it != entities.end())
    {
        return it->second;
    }
    MqttClient &mqtt = Application::inst().getMqttClient();
    OutEntity *entity = new OutEntity(name, pin, this, dynamic_cast<MqttInterface &>(mqtt));
    entities[name] = entity;
    return entity;
}