//
// simpleRGBLED v1.0.1
// 2024.01.22
//

/*----------  Libraries  ----------*/

#include <simpleRGBLED.h>

/*----------  User Variables  ----------*/

#define LED_R   1
#define LED_G   2
#define LED_B   3

/*----------  Program Variables  ----------*/

simpleRGBLED ledStrip(LED_R, LED_G, LED_B);

/*----------  Main Functions  ----------*/

void setup() {
  Serial.begin(115200);

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
