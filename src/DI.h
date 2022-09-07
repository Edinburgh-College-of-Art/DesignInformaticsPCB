#ifndef DI_H
#define DI_H
//------------------------------------------------------------------
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Bounce2.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <DI_Defs.h> //general definitions
#include <CapacitiveSensor.h>

#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
//------------------------------------------------------------------
//Globals for modules
extern Adafruit_NeoPixel LEDS;
extern DHT_Unified TEMP_SENSOR;
extern MFRC522 RFID_READER;
extern Adafruit_ST7735 SCREEN;
//------------------------------------------------------------------
//Globals for buttons
extern Bounce BUTTON_UP;
extern Bounce BUTTON_LEFT;
extern Bounce BUTTON_CENTRE;
extern Bounce BUTTON_RIGHT;
extern Bounce BUTTON_DOWN;
//------------------------------------------------------------------
//Globals for knobs and joystick
extern int JOYSTICK_X;
extern int JOYSTICK_Y;
extern int KNOB_1;
extern int KNOB_2;
//------------------------------------------------------------------
// Globals for Capacitive sensors
extern CapacitiveSensor   CAPACITIVE_TOP;
extern CapacitiveSensor   CAPACITIVE_MIDDLE;
extern CapacitiveSensor   CAPACITIVE_BOTTOM;
extern long CAP_VALUE_TOP;
extern long CAP_VALUE_MIDDLE;
extern long CAP_VALUE_BOTTOM;
//------------------------------------------------------------------
extern int LOOP_COUNTER;
extern bool FIRST;

extern float CURRENT_TEMP;
extern float CURRENT_HUMIDITY;

extern bool RFID_PRESENT;
extern char RFID_ID[20];
extern int RFID_PERSISTENCE;

//------------------------------------------------------------------
// Setup functions
/// Run all setup functions for the DI Board
void setupEverything(bool print = true);
/// Run setup process for the NFC Board
void startNFC(bool print = true);
/// Run Setup process for attache SPI device
void startSPI(bool print = true);
/// Run setup and calibration for the buttons
void startButtons(bool print = true);
/// Run setup for TFT Screen
void startScreen(bool print = true);
/// Run setup for onBoardLEDs
void startLEDs(bool print = true);
/// Run setup for connected Temperture sensor
void startTemperature(bool print = true);

//------------------------------------------------------------------
// Update outputs/context
/// increment the internal loop counter by 1
void updateLoopCounter();
/// Updates the "Watch Dog" LED, the first LED is used for sanity checking board functionality
void updateWatchdogLED();
/// Alias for led.show(), show the output of the current led setting
void outputLEDs();

//------------------------------------------------------------------
// Update inputs
/// update the CURRENT_TEMP and CURRENT_HUMIDITY variables
void updateTemperature(bool print=true);
/// update the Bounce2 type BUTTON_UP, BUTTON_DOWN, BUTTON_LEFT, BUTTON_RIGHT, BUTTON_CENTRE variables
void updateButtons(bool print=true);
/*!
 * Update the RFID Reader
 * This is a bit hacky - I don't understand the library well enough to
 * handle cards appearing and disappearing well. The easy version does something
 * when a card appears, but not necessarily when it disappears.
 *
 * Pretty sure there's a better way to do this!
 */
void updateRFID(bool print=true);
/// updated values of connected potentiometers variables  JOYSTICK_X, JOYSTICK_Y, KNOB_1, KNOB_2
void updateKnobs();
/// Update values of CAP_VALUE_TOP, CAP_VALUE_BOTTOM, CAP_VALUE_MIDDLE
void updateCapacitiveSensors();

//------------------------------------------------------------------
// Utility functions
/// true on every n iterations of loop counter
/// @param n number of loops before true
/// @return true every n cycles
bool oneIn(int n);
//------------------------------------------------------------------
// LED functions

/// colour wipe across all pixels (blocking)
/// @param color colour to wipe
/// @param wait timing between increments of wipe
void colorWipe(uint32_t color, int wait);
/// Convert RGB values to the right format for the SCREEN to show
/// @param R Red
/// @param G Green
/// @param B Blue
word RGBToScreen( byte R, byte G, byte B);

//------------------------------------------------------------------
// Example Display FUNCTIONS
/// Show a static version of the DI Splash screen
void showDISplash();
/// Show a fading in version of the DI Splash screen
void animateDISplash();
/// Light up the built in LEDs in response to the buttons being pressed
void buttonsToLeds();
/*!
 * Maps the humidity and sensor onto an LED ring connected to the LED out port
 * Temperature controls the number of LEDs, and humidity controls the hue
 * Assumes a 16 LED ring connectd to the LED out port on top of the board
 * (should probably add a switch to use the secondary LEDs as well)
 */
void temperatureToLEDRing();

#endif
