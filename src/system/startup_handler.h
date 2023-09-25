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
    StartupHandler()
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
        Preferences preferences;
        preferences.begin("mplc", false);
        // MQTTClient(String client_id, String wifi_ssid, String wifi_password, String mqtt_server, uint16_t mqtt_port, String mqtt_user, String mqtt_password)
        mqttClient = MQTTClient(
            preferences.getString("client_id", CLIENT_ID).c_str(),
            preferences.getString("wifi_ssid", WIFI_SSID).c_str(),
            preferences.getString("wifi_password", WIFI_PASSWORD).c_str(),
            preferences.getString("mqtt_server", MQTT_SERVER).c_str(),
            preferences.getUInt("mqtt_port", MQTT_PORT),
            preferences.getString("mqtt_user", MQTT_USER).c_str(),
            preferences.getString("mqtt_password", MQTT_PASSWORD).c_str());
        preferences.end();

        mqttClient.reconnect();

        gui.init();

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
