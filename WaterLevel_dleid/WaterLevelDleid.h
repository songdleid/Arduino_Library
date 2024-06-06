
#ifndef WATERLEVEL_DLEID_H
#define WATERLEVEL_DLEID_H

#include "Arduino.h"

class WaterLevelDleid
{
public:
    WaterLevelDleid(uint8_t pin);
    void updateLevel();
    void begin();

    bool isLevel;

private:
    uint8_t _pin;
};

#endif // WATERLEVEL_DLEID_H