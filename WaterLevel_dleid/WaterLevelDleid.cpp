/*
   WaterLevelDleid.cpp
  Created:  2024.5.30
  Author:   宋隽颢

  MIT License
  Copyright (c) 2023 MicroBeaut
*/

#include "WaterLevelDleid.h"

WaterLevelDleid::WaterLevelDleid(uint8_t pin): _pin(pin)
{
}
void WaterLevelDleid::begin()
{
  pinMode(_pin, INPUT_PULLUP);
  WaterLevelDleid::updateLevel();
  
}
void WaterLevelDleid::updateLevel()
{
  if(digitalRead(_pin)==LOW)
  {
    this->isLevel = true;
  }else{
    this->isLevel = false;
  }
}