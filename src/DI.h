


#ifndef DI_H
#define DI_H

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
#include <Arduino_LSM6DS3.h>

#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

//Globals for modules
extern Adafruit_NeoPixel LEDS;
extern DHT_Unified TEMP_SENSOR;
extern MFRC522 RFID_READER;
extern Adafruit_ST7735 SCREEN;

//Globals for buttons
extern Bounce BUTTON_UP;
extern Bounce BUTTON_LEFT;
extern Bounce BUTTON_CENTRE;
extern Bounce BUTTON_RIGHT;
extern Bounce BUTTON_DOWN;

//Globals for knobs and joystick
extern int JOYSTICK_X;
extern int JOYSTICK_Y;
extern int KNOB_1;
extern int KNOB_2;

// Globals for Capacitive sensors
extern CapacitiveSensor   CAPACITIVE_TOP;
extern CapacitiveSensor   CAPACITIVE_MIDDLE;
extern CapacitiveSensor   CAPACITIVE_BOTTOM;
extern long CAP_VALUE_TOP;
extern long CAP_VALUE_MIDDLE;
extern long CAP_VALUE_BOTTOM;

// Globals for IMU
extern float ACCEL_X, ACCEL_Y, ACCEL_Z;
extern float GYRO_X, GYRO_Y, GYRO_Z;



extern int LOOP_COUNTER;
extern bool FIRST;

extern float CURRENT_TEMP;
extern float CURRENT_HUMIDITY;

extern bool RFID_PRESENT;
extern char RFID_ID[20];
extern int RFID_PERSISTENCE;


// Setup functions
void setupEverything(bool print = true);
void startNFC(bool print = true);
void startSPI(bool print = true);
void startButtons(bool print = true);
void startScreen(bool print = true);
void startLEDs(bool print = true);
void startTemperature(bool print = true);
void startIMU(bool print = true);

// Update outputs/context
void updateLoopCounter();
void updateWatchdogLED();
void outputLEDs();

// Update inputs
void updateTemperature(bool print=true);
void updateButtons(bool print=true);
void updateRFID(bool print=true);
void updateKnobs();
void updateCapacitiveSensors();
void updateIMU();



// Utility functions
bool oneIn(int n);
void colorWipe(uint32_t color, int wait);
word RGBToScreen( byte R, byte G, byte B);

// Example Display FUNCTIONS
void showDISplash();
void animateDISplash();
void buttonsToLeds();
void temperatureToLEDRing();



#endif
