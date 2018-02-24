# PedZed::ArduinoUtils

_Several useful Arduino classes._

Please star this repo and link to it if you find it useful.


## License
Licensed under MIT. See: [LICENSE](LICENSE).


## Library classes

### Color

A color class to help you with using colors. Useful for RGB leds.

#### Dependencies

_None._

#### Example usage
```cpp
Color selectedColor = Color::green;

Serial.print("R: ");
Serial.print(selectedColor.reds());
Serial.print("G: ");
Serial.print(selectedColor.greens());
Serial.print("B: ");
Serial.print(selectedColor.blues());
Serial.println();
```

### Led

A LED class to help you with using LEDs.

#### Dependencies

_None._

#### Example usage
```cpp
const int DIGITAL_LED_PIN = 13;
const int ANALOG_LED_PIN = A0;

Led digitalLed(DIGITAL_LED_PIN);

Led analogLed(ANALOG_LED_PIN);
int analogLedBrightness = 0;

void setup() {
    digitalLed.turnOn();
}

void loop() {
    analogLed.setBrightness(analogLedBrightness);
    analogLedBrightness++;

    if (analogLedBrightness >= 255) {
        analogLedBrightness = 0;
        digitalLed.toggleOnOrOff();
    }

    digitalLed.update();
    analogLed.update();
}
```

### RgbLed

...

### PushButton

...

### ServoMotor

...

### XyJoystick

...
