#ifndef JOYSTICK_DLEID_H
#define JOYSTICK_DLEID_H

#include <Arduino.h>

class JoyStick_dleid
{
public:
    explicit JoyStick_dleid(HardwareSerial &SerialX);
    bool getUpBtnState();
    bool getDownBtnState();
    bool getLeftBtnState();
    bool getRightBtnState();
    bool getFBtnState();
    bool getEBtnState();
    bool getJoyBtnState();

    int getJognumX();
    int getJognumY();
private:
    HardwareSerial &serial_port;

    static const int UP_BTN = 2;
    static const int DOWN_BTN = 4;
    static const int LEFT_BTN = 5;
    static const int RIGHT_BTN = 3;
    static const int E_BTN = 6;
    static const int F_BTN = 7;
    static const int JOYSTICK_BTN = 8;
    static const int JOYSTICK_AXIS_X = A0;
    static const int JOYSTICK_AXIS_Y = A1;
    static const int buttons[];
};

#endif // JOYSTICK_DLEID_H