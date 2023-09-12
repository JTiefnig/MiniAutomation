#ifndef STARTUP_HANDLER_H
#define STARTUP_HANDLER_H
#include <Arduino.h>
#include "config.h"
#include "system.h"
#include "mini_gui.h"

class StartupHandler
{
private:
    mini_gui gui;
    OpenControlOS ContorlSystem;

public:
    StartupHandler()
    {
    }
    ~StartupHandler()
    {
    }

    void init()
    {
        // init tasks

        gui.init();

        // startup tasks
        xTaskCreatePinnedToCore(controlOSLoop,
                                "SystemLoop",
                                2048,
                                &ContorlSystem,
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
    static void controlOSLoop(void *parameters)
    {
        OpenControlOS *ocos = static_cast<OpenControlOS *>(parameters);
        while (true)
        {
            ocos->loop();
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

    static void miniGuiLoop(void *parameters)
    {
        mini_gui *gui = static_cast<mini_gui *>(parameters);
        while (true)
        {
            gui->loop();
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
};

#endif