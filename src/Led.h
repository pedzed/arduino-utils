#pragma once

#include <stdint.h>

namespace PedZed { namespace ArduinoUtils
{
    enum class LedState {
        OFF,
        ON,
    };

    class Led
    {
        public:
            static const uint8_t DEFAULT_MIN_BRIGHTNESS = 0;
            static const uint8_t DEFAULT_MAX_BRIGHTNESS = 255;

            Led(uint8_t pin);
            uint8_t getPin();

            /**
             * Set the minimum brightness.
             *
             * Used for function chaining. E.g.:
             *
             * led.setMinBrightness(0).turnOff()
             */
            Led &setMinBrightness(uint8_t);
            uint8_t getMinBrightness();

            /**
             * Set the maximum brightness.
             *
             * Used for function chaining. E.g.:
             *
             * led.setMaxBrightness(0).turnOff()
             */
            Led &setMaxBrightness(uint8_t);
            uint8_t getMaxBrightness();

            /**
             * Check and take action.
             *
             * This function needs to be continuously called.
             */
            void update();

            LedState getRequestedState();
            bool isRequestedState(LedState);

            /**
             * Set the fade duration.
             *
             * Used for function chaining. E.g.:
             *
             * led.setFadeDuration(500).turnOff()
             */
            Led &setFadeDuration(uint16_t);

            /**
             * Set the time between each blink.
             *
             * Allows function chaining. E.g.:
             *
             * led.setBlinkInterval(500).blink()
             */
            Led &setBlinkInterval(uint16_t);

            /**
             * Set the blink limit.
             *
             * Allows function chaining. E.g.:
             *
             * led.setBlinkLimit(3).blink()
             */
            Led &setBlinkLimit(uint8_t);

            /**
             * Unset the blink limit.
             *
             * Allows function chaining. E.g.:
             *
             * led.unsetBlinkLimit().blink()
             */
            Led &unsetBlinkLimit();

            /**
             * Set the anode and cathode direction.
             *
             * Used for function chaining. E.g.:
             *
             * led.setInversion(true).turnOff()
             */
            Led &setInversion(bool);
            bool isInverted();

            /**
             * Set a brightness for the ON state.
             *
             * Allows function chaining. E.g.:
             *
             * led.setRequestedBrightness(128).blink()
             */
            Led &setRequestedBrightness(uint8_t);
            uint8_t getRequestedBrightness();

            uint8_t getCurrentBrightness();

            void blink();

            void turnOn();
            void turnOff();
            void toggleOnOrOff();

            bool isOn();
            bool isOff();
            bool isFinishedBlinking();

        private:
            uint8_t pin;

            bool inversion;

            LedState requestedState;

            uint32_t currentTime;

            uint8_t minBrightness;
            uint8_t maxBrightness;

            uint8_t startBrightness;
            uint8_t currentBrightness;
            uint8_t requestedBrightness;
            uint8_t nextBrightness;
            uint16_t fadeDuration;
            uint32_t fadeStartTime;
            uint32_t fadeEndTime;

            bool isBlinking;
            uint16_t blinkInterval;
            uint32_t nextBlinkTime;

            uint8_t blinkLimit;
            uint8_t blinkCount;

            void updateBlinkState();
            void updateOnAndOffState(uint8_t endBrightness);

            /**
             * Prepare the fading.
             *
             * Updates fade variables.
             */
            void prepareFade();
    };
}}
