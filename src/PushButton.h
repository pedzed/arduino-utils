#pragma once

namespace PedZed { namespace ArduinoUtils
{
    class PushButton
    {
        public:
            PushButton(uint8_t pin);
            uint8_t getPin();

            void setPullUpResistor(bool);

            void setInversion(bool);
            bool isInverted();

            void setDebounceMilliseconds(uint32_t);
            uint32_t getDebounceMilliseconds();

            /**
             * This function needs to be continuously called to update the button state data.
             */
            void update();

            bool isPressed();
            bool isPressedForSeconds(uint32_t);
            bool isPressedForMilliseconds(uint32_t);

            bool isReleased();
            bool isReleasedForSeconds(uint32_t);
            bool isReleasedForMilliseconds(uint32_t);

        private:
            uint8_t pin;

            bool inversion;

            /**
             * All times are in milliseconds.
             */
            uint32_t debounceTime;
            uint32_t currentTime;
            uint32_t stateChangedTime;

            bool isCurrentlyPressed;
            bool isPreviouslyPressed;
            bool isStateChanged;

            uint8_t buttonState();
    };
}}
