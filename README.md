# Design Informatics PCB Library

This is a library to make it easy to use the features of the Design Informatics PCB.

## Block Diagram

The main features of the board are here:
![Board Overview](BoardOverview.png)

## Features

* **Screen** - the board has a socket for a [1.44" TFT Screen](https://www.adafruit.com/product/2088), so you can add a display to your projects. This uses the [Adafruit_GFX libaray](https://learn.adafruit.com/adafruit-gfx-graphics-library), so it's easy to do text and graphics
* **LEDs** - there are 9 addressable LEDs on the board - one near the Arduino, and 8 arranged in a circle. These are WS2812Bs, which you can talk to using the [Adafruit NeoPixel Library](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use). There's also a socket to plug more LEDs into this chain, and another socket attached to a different pin for another set of LEDs.
* **Buttons** - there are 5 buttons in a cross - up, down, left, right and one in the middle.
* **Knobs and Joystick** - the little 5 pin joysticks plug in to a socket at the bottom, or you can plug  3 pin potentiometers in at the side
* **Grove Connectors** - there are 6 grove connectors. One for the temp sensor, one for the buttons, two general ones, and two that are set up for [QUIIK](https://www.sparkfun.com/qwiic#products) boards, so you can plug in lots of different fancy sensors quickly
* **Light and Gesture** - a connector for the Proximity, Gesture and Color sensor found on the other arduino boards, the [APDS9960](https://learn.adafruit.com/adafruit-apds9960-breakout).
* **Capacitive Electrodes** - at the top left of the board, there are some hidden capacitive electrodes. These work like buttons, but also sense when you're nearby using the [Capacitive Sensing](https://playground.arduino.cc/Main/CapacitiveSensor/) library.

## Code

To try an make the learning curve a bit easier, the library sets up all of the devices connected to the board (and on the Arduino) and gives you objects that represent them. You get:
 **TODO: Add in all the setup info from DI.h**

 There are also examples that show how this works in practice:
 * ScreenTest makes sure your screen is working
 * LED_Demo will make all the lights flash
 * Everything tries to do everything at once - screen, RFID reader, joystick, buttons, LEDs, Temperature/Humidity, extra LEDs etc.
 * CapacitiveSensors shows the capacitive sensing using the LEDs
 * AccelerometerToLEDs and AccelerometerToScreen both show the Arduino's built in accelerometer, on the LEDs and the screen respectively
