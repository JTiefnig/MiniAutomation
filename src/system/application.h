#ifndef STARTUP_HANDLER_H
#define STARTUP_HANDLER_H
#include <Arduino.h>
#include "config.h"
#include "control_task_scheduler.h"
#include "mini_gui.h"
#include "mqtt_client.h"
#include "temperature_sensor_handler.h"
#include "binary_output_handler.h"
#include "entity_handler.h"
#include <Preferences.h>

class Application
{
private:
    MiniGUI gui;
    ControlTaskScheduler contorlSystem;
    MqttClient mqttClient;

    TemperatureSensorHandler temperatureSensorHandler;

    EntityHandler entityHander;
    Application();
    ~Application();

    static Application *instance;

public:
    static Application &inst();

    // get mqtt client
    MqttClient &getMqttClient();
    // get control system
    ControlTaskScheduler &getControlSystem();
    // get gui
    MiniGUI &getGui();

    TemperatureSensorHandler &getTemperatureSensorHandler()
    {
        return this->temperatureSensorHandler;
    }

    void init();

private:
    static void controlTasksLoop(void *parameters);

    static void miniGuiLoop(void *parameters);
};

#endif
