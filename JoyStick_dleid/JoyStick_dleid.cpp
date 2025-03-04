#include "JoyStick_dleid.h"

#include <Arduino.h>  // 包含Arduino核心库

const int JoyStick_dleid::buttons[] = {UP_BTN, DOWN_BTN, LEFT_BTN, RIGHT_BTN, E_BTN, F_BTN, JOYSTICK_BTN};

JoyStick_dleid::JoyStick_dleid(HardwareSerial &SerialX) : serial_port(SerialX)
{
    for (int i = 0; i < 7; i++)
    {
        pinMode(buttons[i], INPUT_PULLUP);
    }
}
   
   
   
    bool JoyStick_dleid::getUpBtnState()
    {
        return digitalRead(UP_BTN);
    }
    bool JoyStick_dleid::getDownBtnState()
    {
        return digitalRead(DOWN_BTN);
    }
    bool JoyStick_dleid::getLeftBtnState()
    {
        return digitalRead(LEFT_BTN);
    }
    bool JoyStick_dleid::getRightBtnState()
    {
        return digitalRead(RIGHT_BTN);
    }
    bool JoyStick_dleid::getFBtnState()
    {
        return digitalRead(F_BTN);
    }
    bool JoyStick_dleid::getEBtnState()
    {
        return digitalRead(E_BTN);
    }
    bool JoyStick_dleid::getJoyBtnState()
    {
        return digitalRead(JOYSTICK_BTN);
    }

    int JoyStick_dleid::getJognumX()
    {
        return analogRead(JOYSTICK_AXIS_X);
    }
    int JoyStick_dleid::getJognumY()
    {
        return analogRead(JOYSTICK_AXIS_Y);
    }
