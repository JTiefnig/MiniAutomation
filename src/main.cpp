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
#include "startup_handler.h"

#define VERSION "0.0.1"

//  mqtt
MQTTClient client(CLIENT_ID, WIFI_SSID, WIFI_PASSWORD, MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASSWORD);

StartupHandler startup;

void setup()
{
    Serial.begin(115200);
    Serial.println("MPLC Booting");
    Serial.println(VERSION);
    pinMode(LED_BUILTIN, OUTPUT); // debug Status initailisation

    client.reconnect(); //
    startup.init();
}

void loop()
{
    client.loop();

    // MQTT client
    // ArduinoOTA.handle();
}