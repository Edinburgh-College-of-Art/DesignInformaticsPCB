/*
    Accelerometer To LEDs

      In this example, the onboard IMU of the Nano 33 IoT is mapped to the
      on board NeoPixels of the DI Board
*/

#include <DI.h>
//----------------------------------------------------------------
int px = SCREEN_WIDTH / 2;
int py = SCREEN_HEIGHT / 2;
int ball_size = 4;
//----------------------------------------------------------------
word ball_color = ST77XX_RED;
word ball_trail_color = RGBToScreen(30, 60, 90);
//----------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  startIMU();
  startLEDs();
}

void loop()
{
  updateIMU(); // This reads the values into ACCEL_X, ACCEL_Y, ... GYRO_X, ...

  int x_val = (int)(ACCEL_X * 254);
  int y_val = (int)(ACCEL_Y * 254);

  if ( x_val > 0 ) {
    // Set LED colors directly
    // LEDs 3 and 7 are the left and right ones, so we map to the X accelerometer
    LEDS.setPixelColor(3, x_val, 0, 0);
    LEDS.setPixelColor(7, 0, 0, 0);
  } else {
    LEDS.setPixelColor(3, 0, 0, 0);
    LEDS.setPixelColor(7, -x_val, 0, 0);
  }
  
  if ( y_val > 0 ) {
    LEDS.setPixelColor(5, y_val, 0, 0);
    LEDS.setPixelColor(1, 0, 0, 0);
  } else {
    LEDS.setPixelColor(5, 0, 0, 0);
    LEDS.setPixelColor(1, -y_val, 0, 0);
  }

  // Gyro seems to be about -100 to 100, so we'll just use the value directly
  Serial.print(GYRO_X);
  Serial.print(" ");
  Serial.print(GYRO_Y);
  Serial.print("            ");
  
  int xg_val = (int)(GYRO_X);
  int yg_val = (int)(GYRO_Y);
  
  Serial.print(xg_val);
  Serial.print(" " );
  Serial.println(yg_val);

  if ( xg_val > 0 ) {
    LEDS.setPixelColor(4, 0, xg_val, 0);
    LEDS.setPixelColor(8, 0, 0, 0);
  } else {
    LEDS.setPixelColor(4, 0, 0, 0);
    LEDS.setPixelColor(8, 0, -xg_val, 0);
  }
  
  if ( yg_val > 0 ) {
    LEDS.setPixelColor(6, 0, yg_val, 0);
    LEDS.setPixelColor(2, 0, 0, 0);
  } else {
    LEDS.setPixelColor(6, 0, 0, 0);
    LEDS.setPixelColor(2, 0, -yg_val, 0);
  }
  
  outputLEDs();

  delay(30);
}
