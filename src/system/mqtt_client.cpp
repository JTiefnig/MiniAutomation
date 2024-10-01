#include <Arduino.h>
#include "mqtt_client.h"
#include "mqtt_component.h"
#include "helpers.h"
#include "config.h"
#include "application.h"

extern Application app;

MQTTClient::CONNECTION_STATUS MQTTClient::getStatus()
{
    if (WiFi.status() != WL_CONNECTED)
        return MQTTClient::CONNECTION_STATUS::WIFI_DISCONNECTED;
    else if (!this->client.connected())
        return MQTTClient::CONNECTION_STATUS::MQTT_CLIENT_DISCONNECTED;

    return MQTTClient::CONNECTION_STATUS::CONNECTED;
}

MQTTClient::MQTTClient() : wifiClient(), client(wifiClient), credentials()
{
    sendQueue = xQueueCreate(send_queue_len, sizeof(MQMessageBase *));
}

MQTTClient::MQTTClient(const ConnectionCredentials &credentials) : wifiClient(), client(wifiClient), credentials(credentials)
{
    sendQueue = xQueueCreate(send_queue_len, sizeof(MQMessageBase *));
}

MQTTClient::~MQTTClient()
{
}

void MQTTClient::publish(MQMessageBase *msg)
{
    xQueueSend(sendQueue, &msg, 0);
}

void MQTTClient::reconnect()
{
    Serial.print(("Connect Wifi:" + credentials.ssid + " " + credentials.password).c_str());
    WiFi.mode(WIFI_STA);
    while (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(credentials.ssid.c_str(), credentials.password.c_str());
        delay(500);
        Serial.print(".");
        // to gui
        app.getGui().addMessage({"WiFi", MessageType::INFO, "Connecting to WiFi\n" + credentials.ssid, 1000});
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    Serial.print(("Connecting MQTT:\n " + credentials.mqtt_server + "\n " + credentials.mqtt_user + "\n " + credentials.mqtt_password + "\n " + std::to_string(credentials.mqtt_port)).c_str());

    client.setServer(credentials.mqtt_server.c_str(), credentials.mqtt_port);
    // subcribe to all

    client.setCallback([this](char *topic, byte *payload, unsigned int length)
                       { this->receiveCallback(topic, payload, length); });

    while (!client.connected())
    {
        client.connect(credentials.deviceId.c_str(), credentials.mqtt_user.c_str(), credentials.mqtt_password.c_str());
        delay(500);
        Serial.print(".");
    }
    Serial.println("MQTT connected");

    client.subscribe((credentials.deviceId + "/#").c_str());
}

void MQTTClient::loop()
{
    if (getStatus() != CONNECTION_STATUS::CONNECTED)
        reconnect();
    //
    MQMessageBase *currentMessage;
    while (xQueueReceive(sendQueue, &currentMessage, 0) == pdTRUE)
    {
        currentMessage->publish(client);

        delete currentMessage;
    }

    client.loop();
}

void MQTTClient::receiveCallback(char *topic, byte *message, unsigned int length)
{
    std::string messageTemp;

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }

    MQMessage msg = {topic, messageTemp};

    app.getGui().addMessage({msg.topic, MessageType::INFO, msg.topic + " - " + msg.payload, 3000});
    //  todo: improve message rooting by custom mqtt topic callback manager
    for (auto &component : this->components)
    {
        component->processMessage(msg);
    }
}
