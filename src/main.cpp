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
#include "control_tasks/heatingController.h"
#include "system/fixed_state_entity.h"

#define VERSION "0.0.1"

// central application object

void setup()
{
    Serial.begin(115200);
    Serial.println("MPLC Booting");
    Serial.println(VERSION);

    pinMode(LED_BUILTIN, OUTPUT); // debug Status initailisation

    Application &app = Application::inst();

    app.init();

    // initiate 8 OutEntities
    for (int i = 1; i <= 8; i++)
    {
        BinaryOutputHandler::inst().CreateEntity(std::to_string(i), i - 1);
    }

    // example of simple control task to publish sensor data
    app.getControlSystem().addTask(
        new ControlTask(
            []()
            {
                for (auto ent : Application::inst().getTemperatureSensorHandler().getSensorsEntities())
                {
                    ent->publishState();
                }
            },
            2000));

    auto genericEnt = new GenericEntity<int>("timerTest", 97, &app);
    app.getControlSystem().addTask(
        new ControlTask(
            [genericEnt]()
            {
                int val = *genericEnt + 1;
                if (val > 100)
                    *genericEnt = 100;
                else
                    *genericEnt = val;

                Application::inst().getGui().addMessage({"TimerTest", MessageType::INFO, "TimerTest: " + std::to_string(*genericEnt), 1000});
                // genericEnt->publishState();
            },
            1000));

    // example of a fixed state entity with 3 states and callback
    auto fixedStateEnt = new FixedStateEntity("boiler", &app, {"off", "auto", "manual"});
    fixedStateEnt->addCallback([](const EntityBase &ent)
                               { Serial.println(("Callback: " + ent.getName()).c_str()); });

    auto eu_heating_test = new HeatingController("heat_test", &app);

    app.getControlSystem().addTask(eu_heating_test);
    // GenericEntity<int> ent("myent", 3, &app.getMqttClient());

    // Entity ent = app.entityHander.createEntity("mysom", 3);
    // ent.set("ON");
    // ent.addcallback([](std::string msg) { Serial.println(msg.c_str()); });

    // just a delay to ensrue full initalisation of threads
    Serial.println("MPLC Booted");
    vTaskDelay(500 / portTICK_PERIOD_MS);
}

void loop()
{
    Application::inst().getMqttClient().loop();

    // Over the air update
    // ArduinoOTA.handle();
}