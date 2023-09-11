#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

// included wifi
#include <Arduino.h>
#include <functional>
#include <WiFi.h>
#include <PubSubClient.h>
#include <string>
#include <vector>
#include "config.h"

struct MQMessage
{
  char topic[32];
  char message[32];
};

class MQTTClient
{
private:
  QueueHandle_t sendQueue;
  const static int send_queue_len = 10;
  PubSubClient client;
  WiFiClient espClient;

protected:
  const char *deviceId;
  const char *ssid;
  const char *password;
  uint16_t mqtt_port;
  const char *mqtt_server;
  const char *mqtt_user;
  const char *mqtt_password;

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
    if (!client.connected())
      return CONNECTION_STATUS::MQTT_CLIENT_DISCONNECTED;

    return CONNECTION_STATUS::CONNECTED;
  }

  MQTTClient() : espClient(), client(espClient) {}

  MQTTClient(const char *deviceId, const char *ssid,
             const char *password, const char *mqtt_server, uint16_t mqtt_port,
             const char *mqtt_user, const char *mqtt_password)
      : deviceId(deviceId), ssid(ssid), password(password),
        mqtt_server(mqtt_server), mqtt_user(mqtt_user), mqtt_password(mqtt_password), mqtt_port(mqtt_port),
        espClient(), client(espClient)
  {
    sendQueue = xQueueCreate(send_queue_len, sizeof(MQMessage));
  }

  ~MQTTClient()
  {
  }

  // append the message to the queue
  void publish(const char *mytopic, const char *mymsg)
  {
    struct MQMessage mqMessage;
    strcpy(mqMessage.topic, mytopic);
    strcpy(mqMessage.message, mymsg);

    xQueueSend(sendQueue, &mqMessage, 0);
  }

  void reconnect()
  {
    Serial.println("Attempting WIFI connection...");
    int count = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, password);
      vTaskDelay(500);
      count++;
      if (count > 20)
      {
        Serial.println("Could not connect to WiFi. Restarting.");
        ESP.restart();
      }
    }
    Serial.println("connected to WiFi");

    Serial.print(("Attempting MQTT connection to " + std::string(mqtt_server)).c_str());

    client.setServer(mqtt_server, mqtt_port); // MQTT Server, - Por
    for (count = 0; count < 10; count++)
    { // try to connect 10 time
      if (client.connect(deviceId, mqtt_user, mqtt_password))
      {
        // function pointer to the receiveCallback function
        std::function<void(char *, byte *, unsigned int)> receiveCallback =
            std::bind(&MQTTClient::receiveCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        client.setCallback(receiveCallback);
        client.subscribe(deviceId);
        return;
      }
      else
      {
        Serial.print("failed with state ");
        Serial.print(client.state());
        vTaskDelay(500);
      }
      vTaskDelay(500);
    }
    // if all attempts failed, then restart
    // ESP.restart();
    Serial.println("Could not connect to MQTT Server.");
  }

  void loop()
  {
    // Runs as a task on Core zero ir Core 1 but crashes either way
    MQMessage myMessage;
    // if sendQueue has items to send
    while (xQueueReceive(sendQueue, &myMessage, 0) == pdTRUE)
    {
      // Check connections
      if (getStatus() != CONNECTION_STATUS::CONNECTED)
      {
        reconnect();
      }

      client.publish(myMessage.topic, myMessage.message);
    }

    // receive messages
    client.loop();
  }

  void receiveCallback(char *topic, byte *message, unsigned int length)
  {
    Serial.print("topic: ");
    Serial.print(topic);
    Serial.print("Message: ");
    std::string messageTemp;

    for (int i = 0; i < length; i++)
    {
      Serial.print((char)message[i]);
      messageTemp += (char)message[i];
    }
    Serial.println();

    try
    {
      std::vector<std::string> tokens;
      std::string token;
      std::istringstream tokenStream(topic);
      while (std::getline(tokenStream, token, '/'))
      {
        tokens.push_back(token);
      }

      for (auto token : tokens)
      {
        Serial.println(token.c_str());
      }
    }
    catch (const std::exception &e)
    {
      // invalid argument
      return;
    }
  }

  void init()
  {
    reconnect();
  }
};

#endif