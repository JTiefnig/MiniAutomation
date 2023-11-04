#include "binary_output_hander.h"
#include "config.h"

BinaryOutputHandler::BinaryOutputHandler(/* args */) : sr(PIN_SR_DATA, PIN_SR_CLOCK, PIN_SR_LATCH)
{
}

BinaryOutputHandler::~BinaryOutputHandler()
{
}