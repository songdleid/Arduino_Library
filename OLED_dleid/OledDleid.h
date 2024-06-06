/*
  使用方法：
  第一步：引入头文件
  #include "OledDleid.h"
    第二步：类实体化
        #define SCREEN_WIDTH 128 // 设置OLED宽度,单位:像素
        #define SCREEN_HEIGHT 32 // 设置OLED高度,单位:像素

        // 自定义重置引脚,虽然教程未使用,但却是Adafruit_SSD1306库文件所必需的
        #define OLED_RESET 4
        OledDleid oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 4);
    第三步：
    void setup()
    {
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);//前面默认，后面IIC地址
    }
    第四步：
    调用各种函数

*/

#ifndef OLED_DLEID_H
#define OLED_DLEID_H

#include "Arduino.h"

// 引入驱动OLED0.96所需的库
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <oledfont.h>
class OledDleid
{
public:
    OledDleid(uint8_t width, uint8_t height, uint8_t adr,TwoWire *twi = &Wire,uint8_t switchvcc = SSD1306_SWITCHCAPVCC,uint8_t rst_pin = -1, uint32_t clkDuring = 400000UL,
                     uint32_t clkAfter = 100000UL);
    void Englishwords_display(uint8_t x, uint8_t y, const char str[], uint8_t size = 1.5);
    void Englishwords_NoDisplay(uint8_t x, uint8_t y, const char str[], uint8_t size_t);
    void FloatNum_display(uint8_t x, uint8_t y, const float numb,  uint8_t precision,uint8_t size_t);
    void FloatNum_NoDisplay(uint8_t x, uint8_t y, const float numb, uint8_t precision, uint8_t size_t);
    void begin();
    void display();
    ~OledDleid();
    // 绘制进度条
    void drawProgressBar(int x, int y, int width, int height, int progress);
    void displayImage(int x, int y, const uint8_t *imageData,  int width = 128 ,int height = 32);
    void NoDisplayImage(int x, int y, const uint8_t *imageData, int width, int height);
    void clear_RectNOdisplay(uint8_t x, uint8_t y, const char str[], uint8_t size_t);
    void clear_RectDisplay(uint8_t x, uint8_t y, const char str[], uint8_t size_t);
    void clearDisplay();
private:
    Adafruit_SSD1306 Oled_Display;
    uint8_t _width = 32;
    uint8_t _height = 128;
    TwoWire * _twi;
    uint8_t _iicAdr;
    uint8_t _switchvcc;
    bool _connectionState = false;

    const char* floatToString(float value, uint8_t precision);
    bool nonBlockingDelay(unsigned long interval);
    bool OledFound();
    void ConnectionState();
};

#endif // FINITESTATE_H