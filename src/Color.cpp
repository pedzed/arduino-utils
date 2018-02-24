#include "Color.h"

using PedZed::ArduinoUtils::Color;

// Colors: https://www.rapidtables.com/web/color/RGB_Color.html
const Color Color::black(0, 0, 0);
const Color Color::white(255, 255, 255);
const Color Color::red(255, 0, 0);
const Color Color::lime(0, 255, 0);
const Color Color::blue(0, 0, 255);
const Color Color::yellow(255, 255, 0);
const Color Color::cyan(0, 255, 255);
const Color Color::magenta(255, 0, 255);
const Color Color::silver(192, 192, 192);
const Color Color::gray(128, 128, 128);
const Color Color::maroon(128, 0, 0);
const Color Color::olive(128, 128, 0);
const Color Color::green(0, 128, 0);
const Color Color::purple(128, 0, 128);
const Color Color::teal(0, 128, 128);
const Color Color::navy(0, 0, 128);

Color::Color(uint8_t red, uint8_t green, uint8_t blue)
    : r(red), g(green), b(blue)
{
    //
}

uint8_t Color::reds()
{
    return r;
}

uint8_t Color::greens()
{
    return g;
}

uint8_t Color::blues()
{
    return b;
}

uint32_t Color::rgbToHex(uint8_t red, uint8_t green, uint8_t blue)
{
    return (
        ((r & 0xFF) << 16) +
        ((g & 0xFF) << 8) +
        ((b & 0xFF) << 0)
    );
}

uint32_t Color::hex()
{
    return rgbToHex(r, g, b);
}
