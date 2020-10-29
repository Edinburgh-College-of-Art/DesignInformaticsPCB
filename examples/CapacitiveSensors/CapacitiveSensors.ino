#include <DI.h>

void setup()                    
{
   Serial.begin(9600);
   startLEDs();
}


void loop()                    
{
  // Update the sensor values
  updateCapacitiveSensors();
  //Print out the top value, so we have an idea of what we're working with
  Serial.println(CAP_VALUE_TOP);
  delay(10);


  // Color the top 3 LEDs from the first sensor
  // By looking at the values that come in, they are roughly 100-200 with no touch
  // Going up to about 25000 with a finger full on

  // It's nice to control the colour (hue) separately from the brightness, 
  // so we'll use HSV rather than RGB colours
  // The HSV method needs hue in the range 0 - 65535, and saturation and value in 0-255
  // We start by mapping the input to the right range, and then constraining it
  // to make sure nothing funny happens

  // Map the value we've seen (roughly 200 - 25000) into the right range (0-65535)
  int top_hue = map( CAP_VALUE_TOP, 200, 25000, 0, 65535 );
  // Double check it can't go outside the proper range if we get a funny value coming in
  top_hue = constrain( top_hue, 0, 65535 );

  // Same for brightness, but we're mapping to the range 0-255 instead
  int top_brightness = map( CAP_VALUE_TOP, 200, 2500, 0, 255 );
  top_brightness = constrain( top_brightness, 0, 255 );
  uint32_t top_color    = LEDS.ColorHSV(top_hue, 255, top_brightness);
  LEDS.setPixelColor(4, top_color);
  LEDS.setPixelColor(5, top_color);
  LEDS.setPixelColor(6, top_color);

  // Same for the bottom three LEDs, slightly more concisely
  int bottom_hue = constrain( map( CAP_VALUE_BOTTOM, 200, 2500, 0, 65535 ), 0, 65535 );
  int bottom_brightness = constrain( map( CAP_VALUE_BOTTOM, 200, 2500, 0, 255 ), 0, 255 );
  uint32_t bottom_color    = LEDS.ColorHSV(bottom_hue, 255, bottom_brightness);
  LEDS.setPixelColor(1, bottom_color);
  LEDS.setPixelColor(2, bottom_color);
  LEDS.setPixelColor(8, bottom_color);

  // And the two at the sides from the middle sensor
  int middle_hue = constrain( map( CAP_VALUE_MIDDLE, 200, 2500, 0, 65535 ), 0, 65535 );
  int middle_brightness = constrain( map( CAP_VALUE_MIDDLE, 200, 2500, 0, 255 ), 0, 255 );
  uint32_t middle_color    = LEDS.ColorHSV(middle_hue, 255, middle_brightness);
  LEDS.setPixelColor(3, middle_color);
  LEDS.setPixelColor(7, middle_color);
  LEDS.show();

}
