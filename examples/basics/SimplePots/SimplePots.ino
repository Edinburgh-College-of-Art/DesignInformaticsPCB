/*
   Simple Potentiometer Demo

   This example demonstrates how to use the pre-defined KNOB_1 and KNOB_2 vairables.

   connect a potentiometer to the Knob1 and Knob2 pins of the DI board

   Open the Serial Plotter to get a good idea as to the range of values
*/

//--------------------------------------------------------------------------
#include <DI.h>
//--------------------------------------------------------------------------

void setup()
{
  Serial.begin(9600); // Initialize serial communications
  while (!Serial);    // Do nothing until serial port is opened
}

//--------------------------------------------------------------------------

void loop()
{
  updateKnobs();

  Serial.print(KNOB_1);Serial.print(' ');
  Serial.println(KNOB_2);

  delay(25);
}
