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

#ifndef simpleRGBLED_h
#define simpleRGBLED_h

#include "Arduino.h"

class simpleRGBLED {
  public:
    simpleRGBLED(byte, byte, byte);
    void rainbowRoutine();

    String colorHex();
    int colorHue();
    bool status();

    void on();
    void off();
    void toggle();
    void warmWhite();
    void coolWhite();
    void rainbowToggle();

    void setHex(String);
    void setHue(String);
    void setHue(int);
  private:
    byte _rgbPins[3];
    byte _color[3];
    byte _rainbowState = 6;
    bool _isLEDon = false;
    String _colorHex = "000000";
    int _colorHue = 180;

    void writeColor();
    void hexToRGB(char[]);
    void writeHexString();
    void hueToRGB(int);
    void rainbowStep();
};

#endif
