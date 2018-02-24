#pragma once

#include <Servo.h>

namespace PedZed { namespace ArduinoUtils
{
    class ServoMotor
    {
        public:
            static const int16_t SERVO_LIB_MIN_ANGLE = 0;
            static const int16_t SERVO_LIB_MAX_ANGLE = 180;

            static const int16_t DEFAULT_MIN_ANGLE = -90;
            static const int16_t DEFAULT_MAX_ANGLE = 90;
            static const uint16_t DEFAULT_MIN_PULSE_WIDTH = 544;
            static const uint16_t DEFAULT_MAX_PULSE_WIDTH = 2400;

            ServoMotor(uint8_t pin);
            uint8_t getPin();

            void update();

            ServoMotor &setPulseWidthRange(uint16_t min, uint16_t max);
            uint16_t getMinPulseWidth();
            uint16_t getMaxPulseWidth();

            ServoMotor &setInversion(bool);
            bool isInverted();

            ServoMotor &setAngleRange(int16_t min, int16_t max);
            int16_t getMinAngle();
            int16_t getMaxAngle();

            ServoMotor &setSpeed(uint8_t);
            uint8_t getSpeed();

            ServoMotor &setWriteIntervalTime(uint8_t);
            uint8_t getWriteIntervalTime();

            ServoMotor &enable();
            ServoMotor &disable();

            bool isEnabled();
            bool isDisabled();

            void turnToAngle(int16_t);
            int16_t getRequestedAngle();

            int16_t currentAngle();

            bool isRotationFinished();

            Servo getApi();

        private:
            Servo servo;

            uint8_t pin;

            uint16_t minPulseWidth;
            uint16_t maxPulseWidth;

            bool inversion;

            int16_t minAngle;
            int16_t maxAngle;
            int16_t requestedAngle;

            uint8_t speed;

            uint32_t lastWriteTime;
            uint8_t writeIntervalTime;

            int16_t nextAngle();
            int16_t angleRestrainedToRange(uint16_t);
            int16_t angleMappedToLibrary(uint16_t);
    };
}}
