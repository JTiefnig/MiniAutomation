#ifndef MINI_GUI_H
#define MINI_GUI_H

// includes OLED
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SDA1 21
#define SCL1 22

#define OLED_RESET -1

// implement some kind of allert message queue

class MenuElement
{
private:
    std::vector<MenuElement *> children;

public:
    MenuElement(/* args */);
    ~MenuElement();

    virtual void draw(Adafruit_SSD1306 &display) = 0;
    virtual void up() = 0;
    virtual void down() = 0;
    virtual void left() = 0;
    virtual void right() = 0;
    virtual void enter() = 0;
    virtual void back() = 0;
};

enum MessageType
{
    INFO,
    WARNING,
    ERROR
};

struct GuiMessage
{
    std::string title;
    MessageType type;
    std::string msg;
    int displayTime;
    // message queue
};

class MiniGUI
{
private:
    Adafruit_SSD1306 display;
    QueueHandle_t InfoQueue;
    std::map<std::string, GuiMessage> msgs;

public:
    MiniGUI(/* args */) : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
    {
        InfoQueue = xQueueCreate(10, sizeof(GuiMessage *));
    }
    ~MiniGUI() {}

    void init()
    {
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        display.setTextColor(WHITE);
        display.setTextSize(1);

        display.clearDisplay();
        display.setCursor(0, 2);
    }

    // should later serve as a gerneral interface for all updates of ui elements
    void addMessage(const GuiMessage &message)
    {
        auto msg = new GuiMessage(message);
        xQueueSend(InfoQueue, &msg, 0);
    }

    void loop()
    {
        display.clearDisplay();
        display.setCursor(0, 2);
        display.println("MPLC-Testing");

        GuiMessage *message;
        while (xQueueReceive(InfoQueue, &message, 0) == pdTRUE)
        {
            msgs[message->title] = GuiMessage(*message);
            delete message;
        }

        // display all messages
        for (auto &msg : msgs)
        {
            display.println(msg.second.msg.c_str());
            // deduct display time
            msg.second.displayTime -= 100;
            // remove message if display time is over
            if (msg.second.displayTime <= 0)
            {
                msgs.erase(msg.first);
            }
        }

        display.display();

        // delay set for 10Hz refresh rate
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
};

#endif // !MINI_GUI_H