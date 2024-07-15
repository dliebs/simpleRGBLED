//
// simpleRGBLED v1.0.1
// 2024.01.22
//

#ifndef simpleRGBLED_h
#define simpleRGBLED_h

/*----------  Libraries  ----------*/

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
