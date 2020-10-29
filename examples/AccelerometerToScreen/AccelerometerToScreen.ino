#include <DI.h>

int px = SCREEN_WIDTH/2;
int py = SCREEN_HEIGHT/2;
int ball_size = 4;

word ball_color = ST77XX_RED;
word ball_trail_color = RGBToScreen(30,60,90);

void setup() {
  startScreen();
  showDISplash();
  startIMU();
  // put your setup code here, to run once:


}

void loop() {
  // put your main code here, to run repeatedly:
  updateIMU(); // This reads the values into ACCEL_X, ACCEL_Y, ... GYRO_X, ...

  // Cover the previous circle
  SCREEN.fillCircle(px,py,ball_size,ball_trail_color);

  //Update the position based on the accelerometer values.
  //They are roughly in the range -1 to 1.
  //Because map() wants integers, we multiply by 1000 so there is a good range of values
  //from -1000 to 1000. We then map that into the size of the screen
  px = map( (int)(ACCEL_X*1000), 1000, -1000, 0, SCREEN_WIDTH);
  py = map( (int)(ACCEL_Y*1000), -1000, 1000, 0, SCREEN_HEIGHT);
  SCREEN.fillCircle(px,py,ball_size,ball_color);
  delay(30);
}
