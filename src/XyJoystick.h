#pragma once

#include "PushButton.h"

class XyJoystick
{
    private:
        struct Axis
        {
            public:
                Axis(uint8_t pin);
                uint8_t getPin();

                void setRange(uint16_t minValue, uint16_t maxValue);
                uint16_t *getRange();

                void setPrecision(uint8_t);
                uint8_t getPrecision();

                void setInversion(bool);
                bool isInverted();

                int8_t coordinate();
                uint16_t rawInput();
                int8_t percentage();

                bool isNeutral();

            private:
                const uint16_t DEFAULT_MIN_VALUE = 0;
                const uint16_t DEFAULT_MAX_VALUE = 1023;

                uint8_t pin;

                uint16_t minValue;
                uint16_t maxValue;

                uint8_t precision;

                bool inversion;
        };

    public:
        XyJoystick(uint8_t xPin, uint8_t yPin, PushButton *button);

        Axis *getX();
        Axis *getY();
        PushButton *getButton();

        bool isLeft();
        bool isUp();
        bool isRight();
        bool isDown();

        bool isNeutral();

    private:
        Axis *x;
        Axis *y;
        PushButton *button;
};
