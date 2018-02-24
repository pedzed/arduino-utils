#include <Arduino.h>
#include "XyJoystick.h"

XyJoystick::XyJoystick(uint8_t xPin, uint8_t yPin, PushButton *button)
{
    Axis xAxis(xPin);
    Axis yAxis(yPin);

    this->x = &xAxis;
    this->y = &yAxis;
    this->button = button;
}

XyJoystick::Axis *XyJoystick::getX()
{
    return x;
}

XyJoystick::Axis *XyJoystick::getY()
{
    return y;
}

bool XyJoystick::isLeft()
{
    if (getX()->isNeutral()) {
        return false;
    }

    if (getX()->coordinate() > 0) {
        return false;
    }

    return true;
}

bool XyJoystick::isUp()
{
    if (getY()->isNeutral()) {
        return false;
    }

    if (getY()->coordinate() < 0) {
        return false;
    }

    return true;
}

bool XyJoystick::isRight()
{
    if (getX()->isNeutral()) {
        return false;
    }

    return (!isLeft());
}

bool XyJoystick::isDown()
{
    if (getY()->isNeutral()) {
        return false;
    }

    return (!isUp());
}

bool XyJoystick::isNeutral()
{
    return (getX()->isNeutral() && getY()->isNeutral());
}

PushButton *XyJoystick::getButton()
{
    return button;
}

/**
 * Axis for X and Y.
 */
XyJoystick::Axis::Axis(uint8_t pin) : pin(pin)
{
    pinMode(pin, INPUT_PULLUP);
    setRange(DEFAULT_MIN_VALUE, DEFAULT_MAX_VALUE);
    setPrecision(3);
    setInversion(false);
}

uint8_t XyJoystick::Axis::getPin()
{
    return pin;
}

void XyJoystick::Axis::setRange(uint16_t minValue, uint16_t maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}

uint16_t *XyJoystick::Axis::getRange()
{
    uint16_t range[2] = { minValue, maxValue };
    return range;
}

void XyJoystick::Axis::setPrecision(uint8_t precision)
{
    this->precision = precision;
}

uint8_t XyJoystick::Axis::getPrecision()
{
    return precision;
}

void XyJoystick::Axis::setInversion(bool inversion)
{
    this->inversion = inversion;
}

bool XyJoystick::Axis::isInverted()
{
    return (inversion);
}

int8_t XyJoystick::Axis::coordinate()
{
    int8_t coordinate;

    if (inversion) {
        coordinate = map(
            rawInput(),
            minValue,
            maxValue,
            precision,
            -1 * precision
        );
    } else {
        coordinate = map(
            rawInput(),
            minValue,
            maxValue,
            -1 * precision,
            precision
        );
    }

    return coordinate;
}

uint16_t XyJoystick::Axis::rawInput()
{
    return analogRead(pin);
}

int8_t XyJoystick::Axis::percentage()
{
    return ((float) coordinate() / (float) precision) * 100.0;
}

bool XyJoystick::Axis::isNeutral()
{
    return (coordinate() == 0);
}
