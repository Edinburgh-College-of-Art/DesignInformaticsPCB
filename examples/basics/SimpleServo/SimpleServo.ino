/*
   Simple Servo Demo

   This example demonstrates how to connect a Servo with the DI Board

   Connect a servo to the SERVO1 and SERVO2 ports of the DI Board
*/

//--------------------------------------------------------------------------
#include <DI.h>
//--------------------------------------------------------------------------
Servo servo1, servo2;
//--------------------------------------------------------------------------

void setup()
{
  servo1.attach(SERVO_1);
  servo2.attach(SERVO_2);
}

//--------------------------------------------------------------------------

void loop()
{
  for (int pos = 0; pos <= 180; pos += 1)  
  {    
    servo1.write(pos);
    servo2.write(pos);
    delay(15);
  }
  
  for (int pos = 180; pos >= 0; pos -= 1) 
  {
    servo1.write(pos);
    servo2.write(pos);
    delay(15);
  }
}
