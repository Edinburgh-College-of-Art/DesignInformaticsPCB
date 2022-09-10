/*
    Simple Buttons

    This example demonstrates the process of updating and using the pre-defined
    Button variables representing the onboard button pad.
*/
//-----------------------------------------------------------------
#include <DI.h>
//-----------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  startButtons();
}

void loop() {
  updateButtons(false);

  if ( BUTTON_UP.fell() )
    Serial.println("UP");
  if ( BUTTON_DOWN.fell() )
    Serial.println("DOWN");
  if ( BUTTON_LEFT.fell() )
    Serial.println("LEFT");
  if ( BUTTON_RIGHT.fell() )
    Serial.println("RIGHT");
  if ( BUTTON_CENTRE.fell() )
    Serial.println("CENTRE");
}
