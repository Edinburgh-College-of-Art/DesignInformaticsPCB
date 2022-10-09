/*
   Simple NeoPixels

   This example runs through the basic processing for interacting with the onboard LEDs

   Onboard NeoPixels are connected to Pin D21. You can use them with any library directly

   The LEDs variable reperesnts the on board LEDs of the DI Board. LEDs uses the NeoPixel library
   as the framework. See th documentation here:

   https://adafruit.github.io/Adafruit_NeoPixel/html/class_adafruit___neo_pixel.html

   5v Pin NOTE:

      Remember to either solder the 5V tags on the Nano 33 IoT or bridge the VIN and
      5V Pins
*/

//--------------------------------------------------------------------------
#include <DI.h>
//--------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);         // Initialize serial communications
  while (!Serial) delay(10);  // Do nothing until serial port is opened

  setupEverything();
  LEDS.setBrightness(50);  // Set BRIGHTNESS to about 1/5 (max = 255)
}

//--------------------------------------------------------------------------

void loop() {

  LEDS.clear();  // Clear state of all LEDS, turning them off

  for (int i = 0; i < LEDS.numPixels(); i++) {
    LEDS.setPixelColor(i, LEDS.Color(0, 150, 0));
    LEDS.show();
    delay(100);
  }
}