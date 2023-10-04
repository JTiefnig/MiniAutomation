#ifndef STARTUP_HANDLER_H
#define STARTUP_HANDLER_H
#include <Arduino.h>
#include "config.h"
#include "control_task_scheduler.h"
#include "mini_gui.h"
#include "mqtt_client.h"
#include <Preferences.h>

class StartupHandler
{
private:
    MiniGUI gui;
    ControlTaskScheduler contorlSystem;
    MQTTClient mqttClient;

public:
    StartupHandler() : gui(), contorlSystem(), mqttClient()
    {
    }

    ~StartupHandler()
    {
    }

    // get mqtt client
    MQTTClient &getMqttClient()
    {
        return this->mqttClient;
    }
    // get control system
    ControlTaskScheduler &getControlSystem()
    {
        return this->contorlSystem;
    }
    // get gui
    MiniGUI &getGui()
    {
        return this->gui;
    }

    void init()
    {
        // load preferences
        // Preferences preferences;
        // preferences.begin("mplc", false);
        // ConnectionCredentials credentials = {
        //     preferences.getString("client_id", CLIENT_ID).c_str(),
        //     preferences.getString("wifi_ssid", WIFI_SSID).c_str(),
        //     preferences.getString("wifi_password", WIFI_PASSWORD).c_str(),
        //     preferences.getString("mqtt_server", MQTT_SERVER).c_str(),
        //     preferences.getString("mqtt_user", MQTT_USER).c_str(),
        //     preferences.getString("mqtt_password", MQTT_PASSWORD).c_str(),
        //     preferences.getUInt("mqtt_port", MQTT_PORT)};
        // preferences.end();

        auto credentials = ConnectionCredentials({CLIENT_ID, WIFI_SSID, WIFI_PASSWORD, MQTT_SERVER, MQTT_USER, MQTT_PASSWORD, MQTT_PORT});

        gui.init();

        Serial.println("Starting Control System");

        // startup tasks
        xTaskCreatePinnedToCore(controlTasksLoop,
                                "SystemLoop",
                                2048,
                                &contorlSystem,
                                1,
                                NULL,
                                1);

        xTaskCreatePinnedToCore(miniGuiLoop,
                                "GuiLoop",
                                2048,
                                &gui,
                                1,
                                NULL,
                                1);

        // init mqtt client

        mqttClient.init(credentials);
    }

private:
    static void controlTasksLoop(void *parameters)
    {
        ControlTaskScheduler *ocos = static_cast<ControlTaskScheduler *>(parameters);
        while (true)
        {
            ocos->loop();
        }
    }

    static void miniGuiLoop(void *parameters)
    {
        MiniGUI *gui = static_cast<MiniGUI *>(parameters);
        while (true)
        {
            gui->loop();
        }
    }
};

#endif
