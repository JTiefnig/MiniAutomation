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
#include "system/binary_output.h"
#include "system/control_task_scheduler.h"
#include "system/application.h"
#include "system/generic_Entity.h"

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

    // example of simple control task
    app.getControlSystem().addTask(
        new ControlTask(
            []() {},
            1000));

    GenericEntity<int> ent("myent", 3, &app.getMqttClient());

    ent.set(5);
    ent = 6;
    int i = ent;
    Serial.println(i);

    // Entity ent = app.entityHander.createEntity("mysom", 3);
    // ent.set("ON");
    // ent.addcallback([](std::string msg) { Serial.println(msg.c_str()); });

    // just a delay to ensrue full initalisation of threads
    vTaskDelay(500 / portTICK_PERIOD_MS);
}

void loop()
{
    app.getMqttClient().loop();

    // MQTT client
    // ArduinoOTA.handle();
}