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
#include "mqtt_message.h"

class MqttComponent;

class MqttClient
{
public:
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

private:
  QueueHandle_t sendQueue;
  const static uint16_t send_queue_len = 100;
  PubSubClient client;
  WiFiClient wifiClient;
  ConnectionCredentials credentials;

  std::vector<MqttComponent *> components;

public:
  enum CONNECTION_STATUS
  {
    CONNECTED,
    WIFI_DISCONNECTED,
    MQTT_CLIENT_DISCONNECTED
  };

  CONNECTION_STATUS getStatus();

  MqttClient();

  MqttClient(const ConnectionCredentials &credentials);

  // constructor with std::string parameters

  ~MqttClient();

  std::string getDeviceId() const
  {
    return credentials.deviceId;
  }

  // append the message to the queue // todo - use std::string
  void publish(const MqttMsg &msg);

  void reconnect();

  void loop();

  void receiveCallback(char *topic, byte *message, unsigned int length);

  void init(const ConnectionCredentials &credentials)
  {
    this->credentials = credentials;
  }

  void addComponent(MqttComponent *component)
  {
    components.push_back(component);
  }

  void removeComponent(MqttComponent *component)
  {
    components.erase(std::remove(components.begin(), components.end(), component), components.end());
  }
};

#endif