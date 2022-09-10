/*
 * Simple Display Test
 * 
 *  A simple example of the ST7735R TFT Screen for sanity checking
 */

#include <DI.h>

void setup() 
{
  startScreen(); //Setup the screen - it will be an object called SCREEN
  animateDISplash(); //Show an animated version of the DI Logo
}

void loop() {  
}
