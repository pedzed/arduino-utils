#pragma once

#include "Color.h"
#include "Led.h"

namespace PedZed { namespace ArduinoUtils
{
    class RgbLed
    {
        public:
            RgbLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
            ~RgbLed();

            Led *getRedLed();
            Led *getGreenLed();
            Led *getBlueLed();

            /**
             * Check and take action.
             *
             * This function needs to be continuously called.
             */
            void update();

            /**
             * Used for function chaining.
             *
             * E.g.: led.setCommonAnode(true).setColor(Color::blue)
             */
            RgbLed &setCommonAnode(bool);
            bool isCommonAnode();

            /**
             * Used for function chaining.
             *
             * E.g.: led.setCommonCathode(true).setColor(Color::blue)
             */
            RgbLed &setCommonCathode(bool);
            bool isCommonCathode();

            /**
             * Used for function chaining.
             *
             * E.g.: led.setColor(Color::red).blink()
             */
            RgbLed &setColor(Color);
            Color *getColor();
            bool isColor(Color);

            void turnOn();
            void turnOff();
            void toggleOnOrOff();

            bool isOn();
            bool isOff();

        private:
            Led *redLed;
            Led *greenLed;
            Led *blueLed;

            Color *color;

            bool isInverted;
    };
}}
