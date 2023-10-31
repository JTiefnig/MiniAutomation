// INIT VALUES
#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG

#include "../myConfig.h"

// // wifi
// #define WIFI_SSID "<your ssid>"
// #define WIFI_PASSWORD "<your wifi password>"
//
// // mqtt
// #define MQTT_SERVER "<your mqtt server>"
// #define MQTT_USER "<your mqtt user>"
// #define MQTT_PASSWORD "<your mqtt password>"
// #define CLIENT_ID "<your client id>"
// #define MQTT_PORT <your mqtt port>

// Board pin definitions

// shift register
#define PIN_SR_DATA 19
#define PIN_SR_CLOCK 15
#define PIN_SR_LATCH 5
#define NUM_SR 2

#define ONE_WIRE_BUS 4

#endif