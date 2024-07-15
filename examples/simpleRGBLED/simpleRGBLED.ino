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

/*----------  Libraries  ----------*/

#include <simpleRGBLED.h>

/*----------  LED GPIO  ----------*/

#define LED_R   1
#define LED_G   2
#define LED_B   3

/*----------  Program Variables  ----------*/

simpleRGBLED ledStrip(LED_R, LED_G, LED_B);

/*----------  Main Functions  ----------*/

void setup() {
  ledStrip.setHex("#FF0000");
  delay(2000);
  ledStrip.setHex("00FF00");
  delay(2000);
  ledStrip.setHex("#0000FF");
  delay(2000);
  ledStrip.setHex("00FFFF");
  delay(2000);
  ledStrip.setHex("#FF00FF");
  delay(2000);
  ledStrip.setHex("FFFF00");
  delay(2000);
  ledStrip.setHue("0");
  delay(2000);
  ledStrip.setHue(120);
  delay(2000);
  ledStrip.setHue("240");
  delay(2000);
  ledStrip.setHue(145);
  delay(2000);
  ledStrip.off();
  delay(2000);
  ledStrip.on();
  delay(2000);
  ledStrip.toggle();
  delay(2000);
  ledStrip.toggle();
  delay(2000);
  ledStrip.warmWhite();
  delay(2000);
  ledStrip.coolWhite();
  delay(2000);
  ledStrip.rainbowToggle();
}

void loop() {
  ledStrip.rainbowRoutine();
}
