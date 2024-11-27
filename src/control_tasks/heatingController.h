#pragma once

#include "control_task.h"
#include "../system/mqtt_interface.h"
#include "../system/mqtt_message.h"
#include <string>
#include <vector>
#include "../system/generic_Entity.h"
#include "../system/fixed_state_entity.h"
#include <math.h>

class HeatingController : public ControlTaskBase, public MqttInterface
{
    std::string name;
    FixedStateEntity modeState;
    GenericEntity<float> setTemp;
    GenericEntity<float> currentTemp;

public:
    HeatingController(std::string controller_name, MqttInterface &mqtt_interface) : name(controller_name),
                                                                                    ControlTaskBase(5000), MqttInterface(mqtt_interface),
                                                                                    modeState("mode", *this, {"off", "auto", "heat"}),
                                                                                    setTemp("temp", 20.0, *this),
                                                                                    currentTemp("current_temp", 15.0, *this)
    {
        modeState.publishState();
        setTemp.publishState();
        currentTemp.publishState();
    }

    virtual std::string getTopic() const override
    {
        return name;
    }

    virtual ~HeatingController() {}

    void execute() override
    {

        switch (this->modeState.getState())
        {
        case 0:
            Serial.print("Off mode");
            break;
        case 1:
            Serial.print("Auto mode");
            break;
        case 2:
            Serial.print("heat");
            break;
        }

        // simulated controller for testing
        float diff = (setTemp - currentTemp);
        if (abs(diff) > 1)
            currentTemp = currentTemp + diff * 0.1;

        publishState();
    }
};

/*
name: "HeizungStoeckl"
      current_temperature_topic: "esp32/HeizungStoeckl/temp"
      temperature_command_topic: "esp32/HeizungStoeckl/set"
      temperature_state_topic: "esp32/HeizungStoeckl/state"
      temperature_unit: "C"
      min_temp: 15
      max_temp: 60
      temp_step: 1
      modes:
        - "off"
        - "auto"
        - "manual"
      mode_command_topic: "esp32/heat1/mode"
      mode_state_topic: "esp32/heat1/mode_state"
*/