#include "RgbLed.h"

using PedZed::ArduinoUtils::Color;
using PedZed::ArduinoUtils::Led;
using PedZed::ArduinoUtils::LedState;
using PedZed::ArduinoUtils::RgbLed;

RgbLed::RgbLed(uint8_t redPin, uint8_t greenPin, uint8_t bluePin)
{
    redLed = new Led(redPin);
    greenLed = new Led(greenPin);
    blueLed = new Led(bluePin);

    setCommonAnode(true);
}

RgbLed::~RgbLed()
{
    delete redLed;
    delete greenLed;
    delete blueLed;
}

Led *RgbLed::getRedLed()
{
    return redLed;
}

Led *RgbLed::getGreenLed()
{
    return greenLed;
}

Led *RgbLed::getBlueLed()
{
    return blueLed;
}

void RgbLed::update()
{
    getRedLed()->update();
    getGreenLed()->update();
    getBlueLed()->update();
}

RgbLed &RgbLed::setCommonAnode(bool flag)
{
    isInverted = flag;

    getRedLed()->setInversion(flag);
    getGreenLed()->setInversion(flag);
    getBlueLed()->setInversion(flag);

    return *this;
}

bool RgbLed::isCommonAnode()
{
    return (isInverted);
}

RgbLed &RgbLed::setCommonCathode(bool flag)
{
    return setCommonAnode(!flag);
}

bool RgbLed::isCommonCathode()
{
    return !(isCommonAnode());
}

RgbLed &RgbLed::setColor(Color color)
{
    *this->color = color;

    getRedLed()->setRequestedBrightness(color.reds());
    getGreenLed()->setRequestedBrightness(color.greens());
    getBlueLed()->setRequestedBrightness(color.blues());

    return *this;
}

Color *RgbLed::getColor()
{
    return color;
}

bool RgbLed::isColor(Color color)
{
    return (
        getColor()->reds() == color.reds() &&
        getColor()->greens() == color.greens() &&
        getColor()->blues() == color.blues()
    );
}

void RgbLed::turnOn()
{
    getRedLed()->turnOn();
    getGreenLed()->turnOn();
    getBlueLed()->turnOn();
}

void RgbLed::turnOff()
{
    getRedLed()->turnOff();
    getGreenLed()->turnOff();
    getBlueLed()->turnOff();
}

void RgbLed::toggleOnOrOff()
{
    if (getRedLed()->isRequestedState(LedState::ON) ||
        getGreenLed()->isRequestedState(LedState::ON) ||
        getBlueLed()->isRequestedState(LedState::ON)
    ) {
        turnOff();
        return;
    }

    turnOn();
}

bool RgbLed::isOn()
{
    return (!isOff());
}

bool RgbLed::isOff()
{
    return (
        getRedLed()->isOff() &&
        getGreenLed()->isOff() &&
        getBlueLed()->isOff()
    );
}
