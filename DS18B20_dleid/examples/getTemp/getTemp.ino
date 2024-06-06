#include<DS18B20Dleid.h>
DS18B20Dleid Ds18B20Dleid = DS18B20Dleid(31);
 // Addresses of 3 DS18B20s
 uint8_t sensor1[8] = { 0x28, 0x17, 0x18, 0x49, 0xF6, 0xBB, 0x3C, 0x91 };
float temp;
 void setup(void)
 {
   Serial.begin(9600);
 }
 
 void loop(void)
 {
   Ds18B20Dleid.getTemperature(sensor1);
   
   Serial.println(Ds18B20Dleid.tempature);
   delay(1000);
 }