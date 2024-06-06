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

#ifndef RELAY_DLEID_H
#define RELAY_DLEID_H

#include "Arduino.h"

class RelayDleid
{
public:
    RelayDleid(uint8_t pin, bool openHigh = true);
    void open();
    void close();
    void begin();
    bool getNowState();

private:
    uint8_t _pin;
    bool _openHigh;
    bool nowState;
};

#endif // FINITESTATE_H