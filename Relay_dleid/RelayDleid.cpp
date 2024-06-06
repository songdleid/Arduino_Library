/*
   RelayDleid.cpp
  Created:  2024.5.30
  Author:   宋隽颢

  MIT License
  Copyright (c) 2023 MicroBeaut
*/

#include "RelayDleid.h"

RelayDleid::RelayDleid(uint8_t pin, bool openHigh): _pin(pin),_openHigh(openHigh) // 在初始化列表中初始化nowState，而不是在构造函数体内
{
}
void RelayDleid::begin()
{
  pinMode(_pin, OUTPUT);
  RelayDleid::nowState = false;
  RelayDleid::close();
}
void RelayDleid::open()
{
  if (_openHigh)
  {
    digitalWrite(_pin, HIGH);
  }
  else
  {
    digitalWrite(_pin, LOW);
  }
  this->nowState = true;
}
void RelayDleid::close()
{
  if (_openHigh)
  {
    digitalWrite(_pin, LOW);
  }
  else
  {
    digitalWrite(_pin, HIGH);
  }
   this->nowState = false;
}

bool RelayDleid::getNowState()
{
 return this->nowState;
}
