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


  // Color the top 3 LEDs from the first sensor
  uint32_t top_color    = LEDS.ColorHSV(CAP_VALUE_TOP*3, 255, max(CAP_VALUE_TOP/24-2,0));
  LEDS.setPixelColor(4, top_color);
  LEDS.setPixelColor(5, top_color);
  LEDS.setPixelColor(6, top_color);

  // And the bottom three from the bottom sensor
  uint32_t bottom_color = LEDS.ColorHSV(CAP_VALUE_BOTTOM*3, 255, max(CAP_VALUE_BOTTOM/24-2,0));
  LEDS.setPixelColor(1, bottom_color);
  LEDS.setPixelColor(2, bottom_color);
  LEDS.setPixelColor(8, bottom_color);

  // And the two at the sides from the middle sensor
  uint32_t middle_color = LEDS.ColorHSV(CAP_VALUE_MIDDLE*3, 255, max(CAP_VALUE_MIDDLE/24-2,0));
  LEDS.setPixelColor(3, middle_color);
  LEDS.setPixelColor(7, middle_color);
  LEDS.show();

}
