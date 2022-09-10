/*
    Simple Capacative touch

    This example demonstrates how to use the pre-defined CAP_VALUE vairables.

    Open the Serial Plotter to get a good idea as to the range of values

    Pay attention to what range of values appear over time
*/
//-----------------------------------------------------------------
#include <DI.h>
//-----------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.print("TOP"); Serial.print(' ');
  Serial.print("MID"); Serial.print(' ');
  Serial.println("BTM");
}

void loop() {
  updateCapacitiveSensors();
  Serial.print(CAP_VALUE_TOP); Serial.print(' ');
  Serial.print(CAP_VALUE_MIDDLE); Serial.print(' ');
  Serial.println(CAP_VALUE_BOTTOM);
  delay(20);
}
