#pragma once

#include <stdint.h>

namespace PedZed { namespace ArduinoUtils
{
    class Color
    {
        public:
            static const Color black;
            static const Color white;
            static const Color red;
            static const Color lime;
            static const Color blue;
            static const Color yellow;
            static const Color cyan;
            static const Color magenta;
            static const Color silver;
            static const Color gray;
            static const Color maroon;
            static const Color olive;
            static const Color green;
            static const Color purple;
            static const Color teal;
            static const Color navy;

            Color(uint8_t red, uint8_t green, uint8_t blue);

            uint8_t reds();
            uint8_t greens();
            uint8_t blues();

            uint32_t rgbToHex(uint8_t red, uint8_t green, uint8_t blue);
            uint32_t hex();

        private:
            uint8_t r;
            uint8_t g;
            uint8_t b;

    };
}}
