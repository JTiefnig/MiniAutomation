//
//  Mini Automation
//  Author:  Johannes Tiefnig
//  Date:    2023-09-10
//  Version: 0.0.1
//

#include <Arduino.h>

#include <string>
#include <sstream>
#include <iomanip>

#include "system/config.h"
#include "system/mqtt_client.h"
#include "system/mini_gui.h"
#include "system/temperature_sensor.h"
#include "system/output_entity.h"
#include "system/control_task_scheduler.h"
#include "system/startup_handler.h"

#define VERSION "0.0.1"

// handles Startup
StartupHandler startup;

void setup()
{
    Serial.begin(115200);
    Serial.println("MPLC Booting");
    Serial.println(VERSION);
    pinMode(LED_BUILTIN, OUTPUT); // debug Status initailisation

    startup.init();
}

void loop()
{

    startup.getMqttClient().loop();
    // MQTT client
    // ArduinoOTA.handle();
}