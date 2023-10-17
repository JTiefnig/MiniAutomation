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
#include "system/application.h"

#define VERSION "0.0.1"

// handles Startup
extern Application app;

void setup()
{
    Serial.begin(115200);
    Serial.println("MPLC Booting");
    Serial.println(VERSION);
    pinMode(LED_BUILTIN, OUTPUT); // debug Status initailisation

    app.init();

    app.getControlSystem().addTask(new ControlTask([]()
                                                   { app.getGui().addMessage({"Test", MessageType::INFO, "Testing", 2000}); },
                                                   1000));

    for (int i = 0; i < 8; i++)
    {
        new OutEntity(std::to_string(i + 1), i);
    }
}

void loop()
{

    app.getMqttClient().loop();

    // startup.getGui().addMessage({"Test", MessageType::INFO, "Testing", 2000});
    // // serial receive to string
    // std::string input = Serial.readStringUntil('\n').c_str();
    // startup.getGui().addMessage({"input", MessageType::INFO, input, 10000});

    // MQTT client
    // ArduinoOTA.handle();
    // vTaskDelay(1000);
}