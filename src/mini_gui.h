// includes OLED
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <vector>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SDA1 21
#define SCL1 22

#define OLED_RESET -1

// implement some kind of allert message queue

class menu_element
{
private:
    std::vector<menu_element *> children;

public:
    menu_element(/* args */);
    ~menu_element();

    virtual void process(const std::string message) = 0;
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

struct Message
{
    MessageType type;
    std::string text;
    // message queue
};

class mini_gui
{
private:
    Adafruit_SSD1306 display;
    QueueHandle_t InfoQueue;

public:
    mini_gui(/* args */) : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
    {
        InfoQueue = xQueueCreate(10, sizeof(Message));
    }
    ~mini_gui() {}

    void init()
    {
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        display.setTextColor(WHITE);
        display.setTextSize(1);

        display.clearDisplay();
        display.setCursor(0, 2);
    }

    void loop()
    {

        display.clearDisplay();
        display.setCursor(0, 2);
        display.println("Hello World!"); // just testing

        Message message;
        while (xQueueReceive(InfoQueue, &message, 0) == pdTRUE)
        {
            // display message
            display.println(message.text.c_str());
        }

        display.display();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    static void taskEntryPoint(void *parameters)
    {
        mini_gui *gui = static_cast<mini_gui *>(parameters);
        while (true)
            gui->loop();
    }
};