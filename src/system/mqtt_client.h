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
#include "mqtt_interface.h"
#include "mqtt_message.h"

class MqttClient : public MqttInterface
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

  virtual ~MqttClient();

  std::string getDeviceId() const
  {
    return credentials.deviceId;
  }

  // append the message to the queue // todo - use std::string

  void reconnect();

  void loop();

  void receiveCallback(char *topic, byte *message, unsigned int length);

  void init(const ConnectionCredentials &credentials)
  {
    this->credentials = credentials;
  }

  virtual void pushMessage(MqttMsg &msg) override;

  virtual std::string getTopic() const override
  {
    return credentials.deviceId;
  }
};

#endif