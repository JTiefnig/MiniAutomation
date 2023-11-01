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

// central application object
extern Application app;

void setup()
{
    Serial.begin(115200);
    Serial.println("MPLC Booting");
    Serial.println(VERSION);
    pinMode(LED_BUILTIN, OUTPUT); // debug Status initailisation

    app.init();

    for (int i = 0; i < 8; i++)
    {
        new OutEntity(std::to_string(i + 1), i);
    }

    app.getControlSystem().addTask(
        new ControlTask(
            []()
            { app.getTemperatureSensorHandler().publish(app.getMqttClient()); },
            1000));

    // just a delay to ensrue full initalisation of threads
    vTaskDelay(500 / portTICK_PERIOD_MS);
}

void loop()
{
    app.getMqttClient().loop();

    // MQTT client
    // ArduinoOTA.handle();
}