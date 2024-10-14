#include "binary_output_handler.h"
#include "config.h"
#include "application.h"
#include "binary_output.h"

BinaryOutputHandler::BinaryOutputHandler(/* args */) : sr(PIN_SR_DATA, PIN_SR_CLOCK, PIN_SR_LATCH)
{
    Application &app = Application::getInstance();
    // add all pins to the shift register as binary output
    for (int i = 0; i < 8; i++)
    {
        std::string name = std::to_string(i + 1);
        OutEntity *x = new OutEntity(name, i, this, &(app.getMqttClient()));
    }
}

BinaryOutputHandler::~BinaryOutputHandler()
{
}