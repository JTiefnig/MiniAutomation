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

#include "config.h"
#include "mqttClient.h"
#include "mini_gui.h"
#include "temperature_sensor.h"
#include "output_entity.h"
#include "system.h"

#define VERSION "0.0.1"

mini_gui gui;
//  mqtt
MQTTClient client(CLIENT_ID, WIFI_SSID, WIFI_PASSWORD, MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASSWORD);

void setup()
{

    // MQTTClient(const char *deviceId, const char *ssid, const char *password, const char *mqtt_server, u_int16_t mqtt_port, onst char *mqtt_user, const char *mqtt_password)
    //   Initailalize serial communication for Debugging
    Serial.begin(115200);
    Serial.println("MPLC Booting");
    Serial.println(VERSION);

    pinMode(LED_BUILTIN, OUTPUT); // debug Status initailisation

    gui.init();
    client.reconnect(); //

    // setup tasks - can be move to a dedicated task manager class
    // xTaskCreatePinnedToCore(TaskFunction, "TaskName", StackSize, Parameter, Priority, TaskHandle, Core);
    xTaskCreatePinnedToCore(OpenControlOS::loop,
                            "SystemLoop",
                            2048,
                            NULL,
                            1,
                            NULL,
                            1);

    xTaskCreatePinnedToCore(mini_gui::taskEntryPoint,
                            "GuiLoop",
                            2048,
                            &gui,
                            1,
                            NULL,
                            1);
}

void loop()
{
    client.loop();

    // delay task for one second
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    Serial.println("loop");

    // MQTT client
    // ArduinoOTA.handle();
}