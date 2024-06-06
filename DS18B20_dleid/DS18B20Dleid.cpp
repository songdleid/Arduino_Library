/*
  DS18B20Dleid.cpp
  Created:  2024.4.28
  Author:   宋隽颢

  MIT License
  Copyright (c) 2023 MicroBeaut
*/

#include "DS18B20Dleid.h"

/**
 * @brief DS18B20Dleid 构造函数
 *
 * 创建一个 DS18B20Dleid 对象，初始化 OneWire 接口和传感器对象。
 *
 * @param pin OneWire 接口引脚号
 */
DS18B20Dleid::DS18B20Dleid(uint8_t pin) : m_oneWire(pin), m_sensor(&m_oneWire) {
  m_sensor.begin(); // 初始化传感器
}

/**
 * @brief 获取 DS18B20 温度传感器的温度值
 *
 * 通过 DS18B20 温度传感器获取指定设备地址的温度值。
 *
 * @param deviceAddress 设备地址
 *
 * @return 返回温度值（单位：摄氏度）
 */
void  DS18B20Dleid::getTemperature(DeviceAddress deviceAddress)
{
  m_sensor.requestTemperatures();
  this->tempature = m_sensor.getTempC(deviceAddress);
}