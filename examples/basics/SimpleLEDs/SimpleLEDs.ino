/*
   Simple LED Demo

   This example runs through the basic processing for interacting with the onboard LEDs

   Onboard NeoPixels are connected to Pin D21. You can use them with any library directly

   5v Pin NOTE:

      Remember to either solder the 5V tags on the Nano 33 IoT or bridge the VIN and
      5V Pins
*/

//--------------------------------------------------------------------------
#include <DI.h>
//--------------------------------------------------------------------------

void setup()
{
  Serial.begin(9600); // Initialize serial communications
  while (!Serial);    // Do nothing until serial port is opened

  setupEverything();
  LEDS.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

//--------------------------------------------------------------------------

void loop()
{
  // Fill along the length of the strip in various colors...
  colorWipe(LEDS.Color(255,   0,   0), 50);// Red
  colorWipe(LEDS.Color(  0, 255,   0), 50);// Green
  colorWipe(LEDS.Color(  0,   0, 255), 50);// Blue

  // Do a theater marquee effect in various colors...
  theaterChase(LEDS.Color(127, 127, 127), 50); // White, half brightness
  theaterChase(LEDS.Color(127,   0,   0), 50);// Red, half brightness
  theaterChase(LEDS.Color(  0,   0, 127), 50);// Blue, half brightness

  rainbow(10);       // Flowing rainbow cycle along the whole strip
  theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
}

//--------------------------------------------------------------------------
// Some functions of our own for creating animated effects -----------------

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la LEDS.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for (int a = 0; a < 10; a++) { // Repeat 10 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      LEDS.clear(); //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for (int c = b; c < LEDS.numPixels(); c += 3) {
        LEDS.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      LEDS.show(); // Update strip with new contents
      delay(wait); // Pause for a moment
    }
  }
}

// Rainbow cycle along whole LEDS. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < LEDS.numPixels(); i++) { // For each pixel in LEDS...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (LEDS.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / LEDS.numPixels());
      // LEDS.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through LEDS.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      LEDS.setPixelColor(i, LEDS.gamma32(LEDS.ColorHSV(pixelHue)));
    }
    LEDS.show(); // Update strip with new contents
    delay(wait); // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0; // First pixel starts at red (hue 0)
  for (int a = 0; a < 30; a++) { // Repeat 30 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      LEDS.clear(); //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for (int c = b; c < LEDS.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (LEDS.numPixels() steps):
        int hue   = firstPixelHue + c * 65536L / LEDS.numPixels();
        uint32_t color = LEDS.gamma32(LEDS.ColorHSV(hue)); // hue -> RGB
        LEDS.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      LEDS.show(); // Update strip with new contents
      delay(wait); // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
