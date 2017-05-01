//
// Created by nafanya on 01.05.2017.
//

#include <Arduino.h>
#include "Led.h"

namespace NAF {
    Led::Led(uint8_t _pin) {
        pin = _pin;
        status = OFF;
        pinMode(pin, OUTPUT);
        off();
        onTimer.stop();
        offTimer.stop();
    }

    void Led::on() {
        status = ON;
        timerEnabled = false;
        digitalWrite(pin, HIGH);
        onTimer.stop();
        offTimer.stop();
    }

    void Led::off() {
        status = OFF;
        timerEnabled = false;
        digitalWrite(pin, LOW);
        onTimer.stop();
        offTimer.stop();
    }

    void Led::off(uint32_t millis) {
        if (!timerEnabled || status == ONBLINK || status == OFFBLINK) {
            off();
            timerEnabled = true;
            onTimer.stop();
            onTimer.setTimeout(millis);
            onTimer.restart();
        }
    }

    void Led::on(uint32_t millis) {
        if (!timerEnabled || status == ONBLINK || status == OFFBLINK) {
            on();
            timerEnabled = true;
            offTimer.stop();
            offTimer.setTimeout(millis);
            offTimer.restart();
        }
    }

    void Led::blink(uint32_t _millisOn, uint32_t _millisOff) {
        if (!timerEnabled) {
            millisOff = _millisOff;
            millisOn = _millisOn;
            on(millisOn);
            status = ONBLINK;
        }
    }

    void Led::up() {
        if (offTimer.onRestart() && timerEnabled) {
            if (status == ON) {
                off();
                timerEnabled = false;
            } else if (status == ONBLINK) {
                off(millisOff);
                status = OFFBLINK;
            }
        }
        if (onTimer.onRestart() && timerEnabled) {
            if (status == OFF) {
                on();
                timerEnabled = false;
            } else if (status == OFFBLINK) {
                on(millisOn);
                status = ONBLINK;
            }
        }
    }

    bool Led::isOn() {
        return status == ON || status == ONBLINK;
    }
}