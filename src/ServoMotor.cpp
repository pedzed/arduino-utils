#include <Arduino.h>
#include "ServoMotor.h"

using PedZed::ArduinoUtils::ServoMotor;

ServoMotor::ServoMotor(uint8_t pin)
    : pin(pin)
{
    setPulseWidthRange(DEFAULT_MIN_PULSE_WIDTH, DEFAULT_MAX_PULSE_WIDTH);
    setAngleRange(DEFAULT_MIN_ANGLE, DEFAULT_MAX_ANGLE);
    setInversion(false);
    setSpeed(2);
    turnToAngle(0);

    lastWriteTime = 0;
    setWriteIntervalTime(20);
}

uint8_t ServoMotor::getPin()
{
    return pin;
}

void ServoMotor::update()
{
    if (isRotationFinished()) {
        // TODO: Run one more time for correction
        disable();
        return;
    }

    uint32_t currentTime = millis();

    if (currentTime - lastWriteTime < writeIntervalTime) {
        return;
    }

    if (isDisabled()) {
        enable();
    }

    int16_t nextAngle;

    int16_t nextAngle = nextAngle();
    nextAngle = angleRestrainedToRange(nextAngle);
    nextAngle = angleMappedToLibrary(nextAngle);

    servo.write(nextAngle);
    lastWriteTime = currentTime;
}

ServoMotor &ServoMotor::setPulseWidthRange(uint16_t min, uint16_t max)
{
    minPulseWidth = min;
    maxPulseWidth = max;

    return *this;
}

uint16_t ServoMotor::getMinPulseWidth()
{
    return minPulseWidth;
}

uint16_t ServoMotor::getMaxPulseWidth()
{
    return maxPulseWidth;
}

ServoMotor &ServoMotor::setInversion(bool flag)
{
    inversion = flag;
    return *this;
}

bool ServoMotor::isInverted()
{
    return (inversion);
}

ServoMotor &ServoMotor::setAngleRange(int16_t min, int16_t max)
{
    minAngle = min;
    maxAngle = max;

    return *this;
}

int16_t ServoMotor::getMinAngle()
{
    return minAngle;
}

int16_t ServoMotor::getMaxAngle()
{
    return maxAngle;
}

ServoMotor &ServoMotor::setSpeed(uint8_t speed)
{
    this->speed = speed;
    return *this;
}

uint8_t ServoMotor::getSpeed()
{
    return speed;
}

ServoMotor &ServoMotor::setWriteIntervalTime(uint8_t time)
{
    writeIntervalTime = time;
    return *this;
}

uint8_t ServoMotor::getWriteIntervalTime()
{
    return writeIntervalTime;
}

ServoMotor &ServoMotor::enable()
{
    servo.attach(pin, minPulseWidth, maxPulseWidth);
    return *this;
}

ServoMotor &ServoMotor::disable()
{
    servo.detach();
    return *this;
}

bool ServoMotor::isEnabled()
{
    return (servo.attached());
}

bool ServoMotor::isDisabled()
{
    return !(isEnabled());
}

void ServoMotor::turnToAngle(int16_t angle)
{
    requestedAngle = angle;
}

int16_t ServoMotor::getRequestedAngle()
{
    return requestedAngle;
}

int16_t ServoMotor::currentAngle()
{
    return map(
        servo.read(),
        SERVO_LIB_MIN_ANGLE,
        SERVO_LIB_MAX_ANGLE,
        (isInverted()) ? maxAngle : minAngle,
        (isInverted()) ? minAngle : maxAngle
    );
}

int16_t ServoMotor::nextAngle()
{
    return = (requestedAngle > currentAngle()) ? currentAngle() + speed : currentAngle() - speed;
}

int16_t ServoMotor::angleRestrainedToRange(uint16_t angle)
{
    if (nextAngle > maxAngle) {
        return maxAngle;
    }

    if (nextAngle < minAngle) {
        return minAngle;
    }
}

int16_t ServoMotor::angleMappedToLibrary(uint16_t angle)
{
    return map(
        angle,
        (isInverted()) ? maxAngle : minAngle,
        (isInverted()) ? minAngle : maxAngle,
        SERVO_LIB_MIN_ANGLE,
        SERVO_LIB_MAX_ANGLE
    );
}

bool ServoMotor::isRotationFinished()
{
    return (
        currentAngle() > requestedAngle - speed &&
        currentAngle() < requestedAngle + speed
    );
}

Servo ServoMotor::getApi()
{
    return servo;
}
