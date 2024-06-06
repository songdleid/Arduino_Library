

#ifndef DS18B20DLEID_H
#define DS18B20DLEID_H
// 引入驱动所需的库
#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class DS18B20Dleid
{
public:
    DS18B20Dleid(uint8_t pin = 31);
    void getTemperature(DeviceAddress deviceAddress);
    float tempature;
private:
    OneWire m_oneWire;          
    DallasTemperature m_sensor; 
};

#endif // FINITESTATE_H