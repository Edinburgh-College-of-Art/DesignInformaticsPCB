/*
    Buttons to LED

    Interact with the on board LEDs using the button pad

    Left / Right : Select Pixel
    Up / Down    : Change Brightness
    Center       : Toggle Current Colour
*/
//-----------------------------------------------------------------
#include <DI.h>
//-----------------------------------------------------------------
enum Colour {
  RED   = 0xFF0000,
  GREEN = 0x00FF00,
  BLUE  = 0x0000FF
};
Colour currentColourSelection = RED;
int currentLedIndex = 1;
//-----------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  startLEDs();
  startButtons();
  LEDS.updateLength(INTERNAL_LED_COUNT); // set the number of LEDs to only be the number on the DI Board

  LEDS.setPixelColor(currentLedIndex , LEDS.Color(255,   0,   0));
  LEDS.show(); // Update strip with new contents
  setIndicatorLED();
}

void loop() {
  updateButtons(false);

  if ( BUTTON_UP.fell() )
    incCurrentColour()

  if ( BUTTON_DOWN.fell() )
    decCurrentColour();

  if ( BUTTON_LEFT.fell() )
    decLedIndex();

  if ( BUTTON_RIGHT.fell() )
    incLedIndex();

  if ( BUTTON_CENTRE.fell() )
    switchCurrentColourSelection();

}
//-----------------------------------------------------------------
void setIndicatorLED()
{
  LEDS.setPixelColor(0 , 0xFFFFFF & currentColourSelection);
  LEDS.show(); // Update strip with new contents
}
//-----------------------------------------------------------------
void switchCurrentColourSelection()
{
  switch (currentColourSelection)
  {
    case RED:
      currentColourSelection = GREEN;
      break;
    case GREEN:
      currentColourSelection = BLUE;
      break;
    case BLUE:
      currentColourSelection = RED;
      break;
  }
  setIndicatorLED();
}
//-----------------------------------------------------------------
void incLedIndex()
{
  currentLedIndex++;
  if (currentLedIndex == LEDS.numPixels())
    currentLedIndex = LEDS.numPixels() - 1;
  showCurrentPixel();
}

void decLedIndex()
{
  currentLedIndex--;
  if (currentLedIndex == 0)
    currentLedIndex = 1;
  showCurrentPixel();
}

void incCurrentColour()
{
  uint32_t currentColour = LEDS.getPixelColor(currentLedIndex);
  switch (currentColourSelection)
  {
    case RED:
      currentColour += ((currentColour & 0xFF0000) != 0xFF0000) ? 0x330000 : 0;
      break;
    case GREEN:
      currentColour += ((currentColour & 0x00FF00) != 0x00FF00) ? 0x003300 : 0;
      break;
    case BLUE:
      currentColour += ((currentColour & 0x0000FF) != 0x0000FF) ? 0x000033 : 0;
      break;
  }
  LEDS.setPixelColor(currentLedIndex , currentColour);
  LEDS.show(); // Update strip with new contents
}

void decCurrentColour()
{
  uint32_t currentColour = LEDS.getPixelColor(currentLedIndex);
  switch (currentColourSelection)
  {
    case RED:
      currentColour -= (currentColour & 0xFF0000) ? 0x330000 : 0;
      break;
    case GREEN:
      currentColour -= (currentColour & 0x00FF00) ? 0x003300 : 0;
      break;
    case BLUE:
      currentColour -= (currentColour & 0x0000FF) ? 0x000033 : 0;
      break;
  }

  LEDS.setPixelColor(currentLedIndex , currentColour);
  LEDS.show(); // Update strip with new contents
}

void showCurrentPixel()
{
  for (int i = 1; i < LEDS.numPixels(); i++)
  {
    LEDS.setPixelColor(i , (i == currentLedIndex) ? LEDS.Color(255,   0,   0) : 0);
  }
  LEDS.show();
}
