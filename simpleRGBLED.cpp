//
//
//  Simple RGB LED - Version 1.0.2
//  This version was not deployed [2024.01.22]
//
//  Object class for a RGB LED controller
//    simpleRGBLED(LED_R, LED_G, LED_B)
//
//    void rainbowRoutine() - Run every loop
//
//    String colorHex() - returns the current color as a string "XXXXXX"
//    int colorHue() - returns current color as a hue 0-359*
//    bool status() - return true/false for on/off
//
//    void on() - turn LED on
//    void off() - turn LED off
//    void toggle() - toggle LED state
//    void warmWhite() - a warm white
//    void coolWhite() - all LEDs at 100%
//    void rainbowToggle() - enable/disable rainbow mode, setHex/Hue also ends rainbow mode
//
//    void setHex(String) - sets the LED color to hex color string "XXXXXX"
//    void setHue(String) - sets the LED color to a hue string 0-359*
//    void setHue(int) - sets the LED color to a hue int 0-359*
//
//  Changes From Previous Version
//    Comments, cleanup
//
//

#include "simpleRGBLED.h"

// Write GPIO pin numbers to _rgbPins[] and set as output, LOW is off
simpleRGBLED::simpleRGBLED(byte R, byte G, byte B) {
  _rgbPins[0] = R;
  _rgbPins[1] = G;
  _rgbPins[2] = B;

  // LED GPIO
  for (int i = 0; i < 3; i++) {
    pinMode(_rgbPins[i], OUTPUT);
    digitalWrite(_rgbPins[i], LOW);
  }
}

// LED Rainbow, run every loop
void simpleRGBLED::rainbowRoutine() {
  if (_rainbowState < 6) {
    rainbowStep();
    delay(5);
  }
}



String simpleRGBLED::colorHex() {
  return _colorHex;
}

int simpleRGBLED::colorHue() {
  return _colorHue;
}

bool simpleRGBLED::status() {
  return _isLEDon;
}



void simpleRGBLED::on() {
  writeColor();
  writeHexString();
}

void simpleRGBLED::off() {
  for (byte i = 0; i < 3; i++) {
    pinMode(_rgbPins[i], OUTPUT);
    digitalWrite(_rgbPins[i], LOW);
  }
  _rainbowState = 6;
  _colorHex = "000000";
  _isLEDon = false;
}

void simpleRGBLED::toggle() {
  if (_isLEDon) {
    // Turn Off LED
    off();
  }
  else {
    // Turn On LED
    on();
  }
}

void simpleRGBLED::warmWhite() {
  _color[0] = 255;
  _color[1] = 255;
  _color[2] = 126;
  _rainbowState = 6;
  _colorHex = "FFFF7E";
  writeColor();
}

void simpleRGBLED::coolWhite() {
  _color[0] = 255;
  _color[1] = 255;
  _color[2] = 255;
  _rainbowState = 6;
  _colorHex = "FFFF7E";
  writeColor();
}

void simpleRGBLED::rainbowToggle() {
  if (_rainbowState < 6) {
    _rainbowState = 6;
  }
  else {
    _color[0] = 255;
    _color[1] = 0;
    _color[2] = 0;
    writeColor();
    _rainbowState = 0;
  }
}



void simpleRGBLED::setHex(String input) {
  _colorHex = input;

  if ( _colorHex.length() == 7 ) {
    _colorHex.remove(0, 1);
  }

  char colorChar[_colorHex.length() + 1];
  _colorHex.toCharArray(colorChar, sizeof(colorChar));

  hexToRGB(colorChar);

  _rainbowState = 6;
  writeColor();
}

void simpleRGBLED::setHue(String input) {
  _colorHue = input.toInt();

  hueToRGB(_colorHue);

  _rainbowState = 6;
  writeColor();
}

void simpleRGBLED::setHue(int input) {
  _colorHue = input;

  hueToRGB(_colorHue);

  _rainbowState = 6;
  writeColor();
}



/*----------  PRIVATE  ----------*/

// Writes values of _color[] to _rgbPins[], run after any setXXX()
void simpleRGBLED::writeColor() {
  for (byte i = 0; i < 3; i++) {
    if (_color[i] == 0) {
      pinMode(_rgbPins[i], OUTPUT);
      digitalWrite(_rgbPins[i], LOW);
    }
    else {
      analogWrite(_rgbPins[i], _color[i]);
    }
  }
  if (!_isLEDon) { _isLEDon = true; }
}

// Convert hex color to dec and store in _color[]
void simpleRGBLED::hexToRGB(char hex[]) {
  unsigned long colorInt = strtoul(hex, nullptr, 16);

  _color[0] = (colorInt >> 16);
  _color[1] = (colorInt >> 8);
  _color[2] = colorInt;
}

// Write current color[] in dec to _colorHex
void simpleRGBLED::writeHexString() {
  _colorHex = "";
  for (int i = 0; i < 3; i++) {
    if (String(_color[i], HEX).length() < 2) {
      for (int n = String(_color[i], HEX).length(); n > 0; n--) {
        _colorHex += "0";
      }
    }
    _colorHex += String(_color[i], HEX);
  }
}


// Convert hue to RGB (color) (0° = Red, 120° = Green, 240° = Blue)
void simpleRGBLED::hueToRGB(int hue) {
  byte val = 255;
  byte sat = 255;
  byte base = ((255 - sat) * val) >> 8;

  switch (hue / 60) {
    case 0:
      _color[0] = val;
      _color[1] = (((val - base) * hue) / 60) + base;
      _color[2] = base;
      break;

    case 1:
      _color[0] = (((val - base) * (60 - (hue % 60))) / 60) + base;
      _color[1] = val;
      _color[2] = base;
      break;

    case 2:
      _color[0] = base;
      _color[1] = val;
      _color[2] = (((val - base) * (hue % 60)) / 60) + base;
      break;

    case 3:
      _color[0] = base;
      _color[1] = (((val - base) * (60 - (hue % 60))) / 60) + base;
      _color[2] = val;
      break;

    case 4:
      _color[0] = (((val - base) * (hue % 60)) / 60) + base;
      _color[1] = base;
      _color[2] = val;
      break;

    case 5:
      _color[0] = val;
      _color[1] = base;
      _color[2] = (((val - base) * (60 - (hue % 60))) / 60) + base;
      break;
  }
  writeHexString();
}

// Changes the color of the rainbow, run once per loop
void simpleRGBLED::rainbowStep() {
  switch (_rainbowState) {
    case 0:    // R -> Y
      if (_color[1] < 255) {
        _color[1]++;
      }
      if (_color[0] == 255 && _color[1] == 255) {
        _rainbowState++;
      }
      break;

    case 1:    // Y -> G
      if (_color[0] > 0) {
        _color[0]--;
      }
      if (_color[0] == 0 && _color[1] == 255) {
        _rainbowState++;
      }
      break;

    case 2:    // G -> T
      if (_color[2] < 255) {
        _color[2]++;
      }
      if (_color[1] == 255 && _color[2] == 255) {
        _rainbowState++;
      }
      break;

    case 3:    // T -> B
      if (_color[1] > 0) {
        _color[1]--;
      }
      if (_color[1] == 0 && _color[2] == 255) {
        _rainbowState++;
      }
      break;

    case 4:    // B -> M
      if (_color[0] < 255) {
        _color[0]++;
      }
      if (_color[0] == 255 && _color[2] == 255) {
        _rainbowState++;
      }
      break;

    case 5:    // M -> R
      if (_color[2] > 0) {
        _color[2]--;
      }
      if (_color[0] == 255 && _color[2] == 0) {
        _rainbowState = 0;
      }
      break;
  }
  writeColor();
}
