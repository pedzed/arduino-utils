#include <Arduino.h>
#include "Led.h"

using PedZed::ArduinoUtils::Led;
using PedZed::ArduinoUtils::LedState;

Led::Led(uint8_t pin) : pin(pin)
{
    pinMode(pin, OUTPUT);

    setInversion(false);
    setFadeDuration(0);

    isBlinking = false;
    unsetBlinkLimit();
    setBlinkInterval(1000);

    setMinBrightness(DEFAULT_MIN_BRIGHTNESS);
    setMaxBrightness(DEFAULT_MAX_BRIGHTNESS);
    setRequestedBrightness(255);

    currentBrightness = 0;
    turnOff();
}

uint8_t Led::getPin()
{
    return pin;
}

void Led::update()
{
    currentTime = millis();

    if (isBlinking) {
        updateBlinkState();
    }

    uint8_t endBrightness = (isRequestedState(LedState::ON)) ?
        requestedBrightness : getMinBrightness();

    updateOnAndOffState(endBrightness);
}

Led &Led::setInversion(bool flag)
{
    inversion = flag;
    return *this;
}

bool Led::isInverted()
{
    return (inversion);
}

void Led::updateBlinkState()
{
    if (currentTime < nextBlinkTime) {
        return;
    }

    if (isFinishedBlinking()) {
        isBlinking = false;
        return;
    }

    toggleOnOrOff();
    isBlinking = true;
    nextBlinkTime = currentTime + blinkInterval;

    if (isOn()) {
        blinkCount++;
    }
}

bool Led::isFinishedBlinking()
{
    if (blinkLimit == NULL) {
        return false;
    }

    return (blinkCount >= blinkLimit);
}

void Led::updateOnAndOffState(uint8_t endBrightness)
{
    if (currentTime >= fadeEndTime) {
        // Correction
        nextBrightness = endBrightness;
    } else {
        nextBrightness = map(
            currentTime,
            fadeStartTime,
            fadeEndTime,
            startBrightness,
            endBrightness
        );
    }

    if (nextBrightness == currentBrightness) {
        return;
    }

    uint8_t valueToWrite = (isInverted()) ? getMaxBrightness() - nextBrightness : nextBrightness;
    analogWrite(pin, valueToWrite);

    // Update currentBrightness to what used to be the next brightness.
    currentBrightness = nextBrightness;
}

LedState Led::getRequestedState()
{
    return requestedState;
}

bool Led::isRequestedState(LedState state)
{
    return (requestedState == state);
}

Led &Led::setFadeDuration(uint16_t milliseconds)
{
    fadeDuration = milliseconds;
    return *this;
}

Led &Led::setBlinkInterval(uint16_t milliseconds)
{
    blinkInterval = milliseconds;
    return *this;
}

Led &Led::setBlinkLimit(uint8_t limit)
{
    blinkLimit = limit;
    return *this;
}

Led &Led::unsetBlinkLimit()
{
    blinkLimit = NULL;
    return *this;
}

Led &Led::setMinBrightness(uint8_t brightness)
{
    minBrightness = brightness;
    return *this;
}

uint8_t Led::getMinBrightness()
{
    return minBrightness;
}

Led &Led::setMaxBrightness(uint8_t brightness)
{
    maxBrightness = brightness;
    return *this;
}

uint8_t Led::getMaxBrightness()
{
    return maxBrightness;
}

Led &Led::setRequestedBrightness(uint8_t brightness)
{
    requestedBrightness = brightness;
    return *this;
}

uint8_t Led::getRequestedBrightness()
{
    return requestedBrightness;
}

uint8_t Led::getCurrentBrightness()
{
    return currentBrightness;
}

void Led::blink()
{
    blinkCount = 0;
    nextBlinkTime = currentTime + blinkInterval;
    prepareFade();
    isBlinking = true;
}

void Led::prepareFade()
{
    startBrightness = currentBrightness;
    fadeStartTime = currentTime;
    fadeEndTime = fadeStartTime + fadeDuration;
}

void Led::turnOn()
{
    isBlinking = false;
    prepareFade();
    requestedState = LedState::ON;
}

void Led::turnOff()
{
    isBlinking = false;
    prepareFade();
    requestedState = LedState::OFF;
}

void Led::toggleOnOrOff()
{
    (isRequestedState(LedState::ON)) ? turnOff() : turnOn();
}

bool Led::isOn()
{
    return (!isOff());
}

bool Led::isOff()
{
    if (isInverted()) {
        return (currentBrightness == getMaxBrightness());
    }

    return (currentBrightness == getMinBrightness());
}
