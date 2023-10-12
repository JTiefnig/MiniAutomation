#include "application.h"

Application::Application()
    : gui(), contorlSystem(), mqttClient()
{
}

Application::~Application()
{
}

// get mqtt client
MQTTClient &Application::getMqttClient()
{
    return this->mqttClient;
}
// get control system
ControlTaskScheduler &Application::getControlSystem()
{
    return this->contorlSystem;
}
// get gui
MiniGUI &Application::getGui()
{
    return this->gui;
}

void Application::init()
{

    // load preferences
    // this shall be generalized to entities in the future

    Preferences preferences;
    preferences.begin("mplc", false);
    ConnectionCredentials credentials = {
        preferences.getString("client_id", CLIENT_ID).c_str(),
        preferences.getString("wifi_ssid", WIFI_SSID).c_str(),
        preferences.getString("wifi_password", WIFI_PASSWORD).c_str(),
        preferences.getString("mqtt_server", MQTT_SERVER).c_str(),
        preferences.getString("mqtt_user", MQTT_USER).c_str(),
        preferences.getString("mqtt_password", MQTT_PASSWORD).c_str(),
        static_cast<uint16_t>(preferences.getUInt("mqtt_port", MQTT_PORT))};
    preferences.end();

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

void Application::controlTasksLoop(void *parameters)
{
    ControlTaskScheduler *ocos = static_cast<ControlTaskScheduler *>(parameters);
    while (true)
    {
        ocos->loop();
    }
}

void Application::miniGuiLoop(void *parameters)
{
    MiniGUI *gui = static_cast<MiniGUI *>(parameters);
    while (true)
    {
        gui->loop();
    }
}

Application app;