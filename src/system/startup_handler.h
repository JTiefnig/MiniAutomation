#ifndef STARTUP_HANDLER_H
#define STARTUP_HANDLER_H
#include <Arduino.h>
#include "config.h"
#include "control_task_manager.h"
#include "mini_gui.h"

class StartupHandler
{
private:
    mini_gui gui;
    ControlTaskManager ContorlSystem;

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
        xTaskCreatePinnedToCore(controlTasksLoop,
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
    static void controlTasksLoop(void *parameters)
    {
        ControlTaskManager *ocos = static_cast<ControlTaskManager *>(parameters);
        while (true)
        {
            ocos->loop();
        }
    }

    static void miniGuiLoop(void *parameters)
    {
        mini_gui *gui = static_cast<mini_gui *>(parameters);
        while (true)
        {
            gui->loop();
        }
    }
};

#endif
