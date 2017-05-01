//
// Created by nafanya on 01.05.2017.
//

#ifndef NAF_LED_H
#define NAF_LED_H

#include <Arduino.h>
#include "../../Timer/src/Timer.h"

namespace NAF {
    class Led {
    public:
        Led(uint8_t _pin);
        void off();
        void off(uint32_t millis);
        void on();
        void on(uint32_t millis);
        void blink(uint32_t millisOn, uint32_t millisOff);
        void up();
        bool isOn();
    private:
        uint8_t pin;
        NAF::Timer onTimer, offTimer;
        enum {ON, OFF, ONBLINK, OFFBLINK} status = OFF;
        bool timerEnabled = false;
        uint32_t millisOn, millisOff;
    };
}


#endif //NAF_LED_H
