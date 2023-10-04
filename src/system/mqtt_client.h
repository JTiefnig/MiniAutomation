#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

// included wifi
#include <Arduino.h>
#include <functional>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>
#include <vector>
#include "config.h"
#include "helpers.h"
#include "mqtt_component.h"

struct MQMessage
{
  std::string topic;
  std::string message;
};

struct ConnectionCredentials
{
  std::string deviceId;
  std::string ssid;
  std::string password;
  std::string mqtt_server;
  std::string mqtt_user;
  std::string mqtt_password;
  uint16_t mqtt_port;
};

class MQTTClient
{
private:
  QueueHandle_t sendQueue;
  const static uint16_t send_queue_len = 100;
  PubSubClient client;
  WiFiClient wifiClient;

  ConnectionCredentials credentials;

public:
  enum CONNECTION_STATUS
  {
    CONNECTED,
    WIFI_DISCONNECTED,
    MQTT_CLIENT_DISCONNECTED
  };

  CONNECTION_STATUS getStatus()
  {
    if (WiFi.status() != WL_CONNECTED)
      return CONNECTION_STATUS::WIFI_DISCONNECTED;
    if (this->client.connected() == false)
      return CONNECTION_STATUS::MQTT_CLIENT_DISCONNECTED;

    return CONNECTION_STATUS::CONNECTED;
  }

  MQTTClient() : wifiClient(), client(wifiClient), credentials()
  {
    sendQueue = xQueueCreate(send_queue_len, sizeof(MQMessage *));
  }

  MQTTClient(const ConnectionCredentials &credentials) : wifiClient(), client(wifiClient), credentials(credentials)
  {
    sendQueue = xQueueCreate(send_queue_len, sizeof(MQMessage *));
  }

  // constructor with std::string parameters

  ~MQTTClient()
  {
  }

  // append the message to the queue // todo - use std::string
  void publish(const char *sendtopic, const char *sendmsg)
  {
    auto msg = new MQMessage({sendtopic, sendmsg});
    xQueueSend(sendQueue, &msg, 0);
  }

  void reconnect()
  {

    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(credentials.ssid.c_str(), credentials.password.c_str());
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    client.setServer(credentials.mqtt_server.c_str(), credentials.mqtt_port);
    // subcribe to all

    client.setCallback([this](char *topic, byte *payload, unsigned int length)
                       { this->receiveCallback(topic, payload, length); });

    client.connect(credentials.deviceId.c_str(), credentials.mqtt_user.c_str(), credentials.mqtt_password.c_str());

    client.subscribe("#");
  }

  void loop()
  {
    if (getStatus() != CONNECTION_STATUS::CONNECTED)
    {
      reconnect();
    }

    // Runs as a task on Core zero ir Core 1 but crashes either way
    MQMessage *currentMessage;
    // if sendQueue has items to send
    while (xQueueReceive(sendQueue, &currentMessage, 0) == pdTRUE)
    {
      Serial.print("Sending message: ");
      Serial.print(currentMessage->topic.c_str());
      Serial.print(" ");
      Serial.println(currentMessage->message.c_str());

      client.publish(currentMessage->topic.c_str(), currentMessage->message.c_str());
      delete currentMessage;
    }

    client.loop();
  }

  void receiveCallback(char *topic, byte *message, unsigned int length)
  {
    // write to serial
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;
    for (int i = 0; i < length; i++)
    {
      Serial.print((char)message[i]);
      messageTemp += (char)message[i];
    }
    Serial.println(messageTemp.c_str());
  }

  void init(const ConnectionCredentials &credentials)
  {
    this->credentials = credentials;
    reconnect();
  }
};

#endif