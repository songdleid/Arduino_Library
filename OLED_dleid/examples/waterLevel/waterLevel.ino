#include<DS18B20Dleid.h>

#include "OledDleid.h"
#define D32_PIN 32
//128-32屏幕宽度 
//自定义重置引脚,虽然教程未使用
OledDleid oled(128, 32,0x3C, &Wire,SSD1306_SWITCHCAPVCC,4);

DS18B20Dleid Ds18B20Dleid = DS18B20Dleid(31);
 // Addresses of 3 DS18B20s
 uint8_t sensor1[8] = { 0x28, 0x17, 0x18, 0x49, 0xF6, 0xBB, 0x3C, 0x91 };
  float d32_state;
  float d32_stateOld;
char buffer[20];
void setup(void)
{
  pinMode(D32_PIN, INPUT_PULLUP);
  oled.begin();//前面默认，后面IIC地址
  Serial.begin(9600);
  oled.Englishwords_display(25, 5, "level:", 1);
}
 
 void loop(void)
 {
    // 读取 D32 端口的电平
    d32_state = digitalRead(D32_PIN);
    oled.FloatNum_display(60, 5, d32_state, 0,1);
    Serial.println(d32_state);
}