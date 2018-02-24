#include <Arduino.h>
#include "PushButton.h"

using PedZed::ArduinoUtils::PushButton;

PushButton::PushButton(uint8_t pin) :
    pin(pin)
{
    pinMode(pin, INPUT);

    setPullUpResistor(true);
    setInversion(true);
    setDebounceMilliseconds(20);

    isCurrentlyPressed = buttonState();
    isPreviouslyPressed = isCurrentlyPressed;
    isStateChanged = false;

    currentTime = millis();
    stateChangedTime = currentTime;
}

uint8_t PushButton::getPin()
{
    return pin;
}

void PushButton::setPullUpResistor(bool pullUp)
{
    // If the pin is configured as an INPUT, digitalWrite() will enable (HIGH)
    // or disable (LOW) the internal pullup on the input pin.
    // @url https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/
    digitalWrite(pin, (pullUp) ? HIGH : LOW);
}

void PushButton::setInversion(bool inversion)
{
    this->inversion = inversion;
}

bool PushButton::isInverted()
{
    return (inversion);
}

void PushButton::setDebounceMilliseconds(uint32_t ms)
{
    debounceTime = ms;
}

uint32_t PushButton::getDebounceMilliseconds()
{
    return debounceTime;
}

uint8_t PushButton::buttonState()
{
    return (inversion) ? !digitalRead(pin) : digitalRead(pin);
}

void PushButton::update()
{
    currentTime = millis();

    if ((currentTime - stateChangedTime) < debounceTime) {
        isStateChanged = false;
        return;
    }

    // Updates old "is previously pressed" value to new "is previously pressed" value
    isPreviouslyPressed = isCurrentlyPressed;
    isCurrentlyPressed = buttonState();

    isStateChanged = !(isCurrentlyPressed == isPreviouslyPressed);

    if (isStateChanged) {
        stateChangedTime = currentTime;
    }
}

bool PushButton::isPressed()
{
    return (isCurrentlyPressed && isStateChanged);
}

bool PushButton::isPressedForSeconds(uint32_t s)
{
    return (isPressedForMilliseconds(s * 1000));
}

bool PushButton::isPressedForMilliseconds(uint32_t ms)
{
    return (isCurrentlyPressed && (currentTime - stateChangedTime) >= ms);
}

bool PushButton::isReleased()
{
    return (!isCurrentlyPressed && isStateChanged);
}

bool PushButton::isReleasedForSeconds(uint32_t s)
{
    return (isReleasedForMilliseconds(s * 1000));
}

bool PushButton::isReleasedForMilliseconds(uint32_t ms)
{
    return (!isCurrentlyPressed && (currentTime - stateChangedTime) >= ms);
}
