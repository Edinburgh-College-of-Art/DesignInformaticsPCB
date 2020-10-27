#include <DI.h>


Bounce BUTTON_UP = Bounce();
Bounce BUTTON_LEFT = Bounce();
Bounce BUTTON_CENTRE = Bounce();
Bounce BUTTON_RIGHT = Bounce();
Bounce BUTTON_DOWN = Bounce();



DHT_Unified TEMP_SENSOR(TEMPERATURE_PIN, TEMPERATURE_TYPE);

MFRC522 RFID_READER(RFID_SS_PIN, RFID_RST_PIN);  // Create MFRC522 instance

Adafruit_ST7735 SCREEN = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

Adafruit_NeoPixel LEDS(INTERNAL_LED_WITH_RING_COUNT, INTERNAL_LED_PIN, NEO_GRB + NEO_KHZ800);

CapacitiveSensor   CAPACITIVE_TOP = CapacitiveSensor(CAPACITIVE_RETURN_PIN,CAPACITIVE_TOP_PIN);        // Top one
CapacitiveSensor   CAPACITIVE_MIDDLE = CapacitiveSensor(CAPACITIVE_RETURN_PIN,CAPACITIVE_MIDDLE_PIN);        // Middle
CapacitiveSensor   CAPACITIVE_BOTTOM = CapacitiveSensor(CAPACITIVE_RETURN_PIN,CAPACITIVE_BOTTOM_PIN);        // Bottom

// GLOBAL VARIABLES
// Watchdog/loop
long _WATCHDOG_HUE = 0;
int _WATCHDOG_VALUE = 0;
int LOOP_COUNTER = 0;
bool FIRST = true;

// Temp/humidity
float CURRENT_TEMP = 0.0;
float CURRENT_HUMIDITY = 0.0;

// RFID Reading
bool RFID_PRESENT = false;
char RFID_ID[20] = "XXXXXXXX";
int RFID_PERSISTENCE = 1;
int _RFID_ABSENCE = 0;

int JOYSTICK_X = 0;
int JOYSTICK_Y = 0;
int KNOB_1 = 0;
int KNOB_2 = 0;

// Capactive sensor data
long CAP_VALUE_TOP = 0;
long CAP_VALUE_MIDDLE = 0;
long CAP_VALUE_BOTTOM = 0;


// Check if things have been started
bool _SPI_STARTED = false;

void setupEverything(bool print) {
  // put your setup code here, to run once:
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  Serial.print("Starting everything... Printing: ");
  Serial.println(print);
  startScreen(print);
  showDISplash();
  startLEDs(print);
  startNFC(print);
  startButtons(print);
  startTemperature(print);
}

/*
 *****************************************
 * SETUP FUNCTIONS
 *****************************************
 */

void startLEDs(bool print) {
  //LEDS
  if( print ) Serial.print("Starting LEDs... ");
  LEDS.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  LEDS.show();            // Turn OFF all pixels ASAP
  LEDS.setBrightness(255); // Set BRIGHTNESS to full (max = 255)
  if( print ) Serial.println("OK");
}


void startNFC(bool print) {
  if( print ) Serial.print("Starting NFC... ");
  startSPI(print);
  RFID_READER.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  if(print) RFID_READER.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  if( print ) Serial.println("OK");
}

void startSPI(bool print) {
  if(_SPI_STARTED) return;
  _SPI_STARTED = true;
  SPI.begin();      // Init SPI bus
}

void startButtons(bool print) {  //Buttons
  if( print ) Serial.print("Starting buttons... ");
  pinMode(BUT_UP,INPUT_PULLUP);
  BUTTON_UP.attach(BUT_UP);
  BUTTON_UP.interval(5); // interval in
  pinMode(BUT_LEFT,INPUT_PULLUP);
  BUTTON_LEFT.attach(BUT_LEFT);
  BUTTON_LEFT.interval(5); // interval in
  pinMode(BUT_CENT,INPUT_PULLUP);
  BUTTON_CENTRE.attach(BUT_CENT);
  BUTTON_CENTRE.interval(5); // interval in
  pinMode(BUT_RIGHT,INPUT_PULLUP);
  BUTTON_RIGHT.attach(BUT_RIGHT);
  BUTTON_RIGHT.interval(5); // interval in
  pinMode(BUT_DOWN,INPUT_PULLUP);
  BUTTON_DOWN.attach(BUT_DOWN);
  BUTTON_DOWN.interval(5); // interval in
  if( print ) Serial.println("OK");
}

void startScreen(bool print) {
  // Screen
  if( print ) Serial.print("Starting Screen... ");
  SCREEN.initR(INITR_144GREENTAB); // Initialise display
  //tft.setRotation(1);
  SCREEN.setTextSize(0);
  SCREEN.setCursor(0, 0);
  SCREEN.setTextWrap(true);
  SCREEN.fillScreen(ST77XX_WHITE);
  SCREEN.setTextColor(ST77XX_BLACK);
  SCREEN.print("design informatics");
  if( print ) Serial.print("OK");
}

void startTemperature(bool print) {
  //Temp
  if( print ) Serial.print("Starting Temperature sensor... ");
  TEMP_SENSOR.begin();
  if( print ) Serial.println("OK");
}


/*
 *****************************************
 * UPDATE FUNCTIONS
 *****************************************
 */

 void updateTemperature(bool print) {
   // Should be checking when we last updated temp and returning if not enough time passed...
   //if( loop_counter % 100 && ! first) return;
   // Get temperature event and print its value.
   sensors_event_t event;
   TEMP_SENSOR.temperature().getEvent(&event);
   if (isnan(event.temperature)) {
     if(print) { Serial.println(F("Error reading temperature!")); }
   }
   else {
     CURRENT_TEMP = event.temperature;
     if(print) {
       Serial.print(F("Temperature: "));
       Serial.print(event.temperature);
       Serial.println(F("°C"));
     }
   }
   // Get humidity event and print its value.
   TEMP_SENSOR.humidity().getEvent(&event);
   if (isnan(event.relative_humidity)) {
     if( print ) {
       Serial.println(F("Error reading humidity!"));
     }
   }
   else {
     CURRENT_HUMIDITY = event.relative_humidity;
     if( print ) {
       Serial.print(F("Humidity: "));
       Serial.print(event.relative_humidity);
       Serial.println(F("%"));
     }
   }

 }

 void updateButtons(bool print) {
   BUTTON_UP.update();
   BUTTON_LEFT.update();
   BUTTON_RIGHT.update();
   BUTTON_CENTRE.update();
   BUTTON_DOWN.update();
   if(print) {
     Serial.print("Buttons: ");
     Serial.print(BUTTON_UP.fell()       ? "UP     " : "       ");
     Serial.print(BUTTON_DOWN.fell()     ? "DOWN   " : "       ");
     Serial.print(BUTTON_LEFT.fell()     ? "LEFT   " : "       ");
     Serial.print(BUTTON_RIGHT.fell()    ? "RIGHT  " : "       ");
     Serial.print(BUTTON_CENTRE.fell()   ? "CENTRE " : "       ");
     Serial.println();
   }
 }

 /*
  * Update the RFID Reader
  * This is a bit hacky - I don't understand the library well enough to
  * handle cards appearing and disappearing well. The easy version does something
  * when a card appears, but not necessarily when it disappears.
  *
  * Pretty sure there's a better way to do this!
  */
void updateRFID(bool print) {
 // Look for a new card
 RFID_READER.PICC_IsNewCardPresent();

 // Try to read from a card if present
 if ( RFID_READER.PICC_ReadCardSerial()) {
   //Serial.println("Card present!");
   RFID_PRESENT = true;

   // Dump debug info about the card; PICC_HaltA() is automatically called
   //mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));
   byte* uidByte = RFID_READER.uid.uidByte;
   sprintf(RFID_ID,"%02X%02X%02X%02X",uidByte[0],uidByte[1],uidByte[2],uidByte[3]);
   _RFID_ABSENCE = 0;
   //mfrc522.PICC_HaltA();
 }
 else {
   if( _RFID_ABSENCE > RFID_PERSISTENCE ) {
     RFID_PRESENT = false;
     sprintf(RFID_ID,"None    ");
   } else {
     _RFID_ABSENCE ++;
   }
 }

 if( print ) {
   Serial.print("Got card: ");
   Serial.print(RFID_PRESENT);
   Serial.print("  ID: ");
   Serial.println(RFID_ID);
 }
}

void updateKnobs() {
  JOYSTICK_X = analogRead(JOYSTICK_X_PIN);
  JOYSTICK_Y = analogRead(JOYSTICK_Y_PIN);
  KNOB_1 = JOYSTICK_X;
  KNOB_2 = JOYSTICK_Y;
}

void updateCapacitiveSensors() {
  CAP_VALUE_TOP = CAPACITIVE_TOP.capacitiveSensor(30);
  CAP_VALUE_MIDDLE = CAPACITIVE_MIDDLE.capacitiveSensor(30);
  CAP_VALUE_BOTTOM = CAPACITIVE_BOTTOM.capacitiveSensor(30);
}


/*
 * Update the loop counter
 */
void updateLoopCounter() {
  LOOP_COUNTER = (LOOP_COUNTER + 1 ) % 1000;
  FIRST = false;
}

/*
 * Update the watchdog LED - lets you know the board is working
 */
void updateWatchdogLED() {
  _WATCHDOG_HUE = (_WATCHDOG_HUE + 50) % 65535;
  _WATCHDOG_VALUE = (_WATCHDOG_VALUE + 1 ) % 512;
  LEDS.setPixelColor(0, LEDS.ColorHSV(_WATCHDOG_HUE, 255, abs(_WATCHDOG_VALUE-255)));
}

void outputLEDs() {
  LEDS.show();
}


/*
 *****************************************
 * UTILITY FUNCTIONS
 *****************************************
 */


/*
 * Execute the function one every N cycles
 * but also on startup
 */
bool oneIn(int n) {
  if( LOOP_COUNTER == 0 ) return true;
  if( LOOP_COUNTER % n == 0 ) return true;
  return false;
}

/*
 * Convert RGB values to the right format for the SCREEN to show
 */
word RGBToScreen( byte R, byte G, byte B) {
  return ( ((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3) );
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// LEDS.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<LEDS.numPixels(); i++) { // For each pixel in LEDS...
    LEDS.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    LEDS.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}


/*
 *****************************************
 * EXAMPLE FUNCTIONS
 *****************************************
 */



/*
 * Show a fading in version of the DI Splash screen
 */
void animateDISplash() {
  //Setup display for text
  SCREEN.setTextSize(0);
  SCREEN.setTextWrap(true);
  SCREEN.fillScreen(ST77XX_WHITE);
  SCREEN.setFont(&FreeSansBoldOblique9pt7b);
  SCREEN.setCursor(0, 30);
  SCREEN.setTextColor(RGBToScreen(128,128,128));
  SCREEN.setFont(&FreeSansBold12pt7b);
  SCREEN.print("Welcome");
  SCREEN.setFont(&FreeSansBold9pt7b);
  SCREEN.print("\nto");

   // Fade text in
  for( int i = 0; i <= 255; i += 2 ) {
    int level = 255 - i;
    SCREEN.setCursor(0, 80);
    SCREEN.setFont(&FreeSansBoldOblique9pt7b);
    SCREEN.setTextColor(RGBToScreen(level,level,level));
    SCREEN.print("  design\n  informatics");
    delay(10);
  }
}

/*
 * Show a static version of the DI Splash screen
 */
void showDISplash() {
  //Setup display for text
  SCREEN.setTextSize(0);
  SCREEN.setTextWrap(true);
  SCREEN.fillScreen(ST77XX_WHITE);
  SCREEN.setFont(&FreeSansBoldOblique9pt7b);
  SCREEN.setCursor(0, 30);
  SCREEN.setTextColor(RGBToScreen(128,128,128));
  SCREEN.setFont(&FreeSansBold12pt7b);
  SCREEN.print("Welcome");
  SCREEN.setFont(&FreeSansBold9pt7b);
  SCREEN.print("\nto");
  SCREEN.setCursor(0, 80);
  SCREEN.setFont(&FreeSansBoldOblique9pt7b);
  SCREEN.setTextColor(ST77XX_BLACK);
  SCREEN.print("  design\n  informatics");
}


// Light up the built in LEDs in response to the buttons being pressed
void buttonsToLeds() {
  uint32_t BLACK = LEDS.Color(0,0,0);
    // If the centre button is pressed, we'll be green, otherwise red
  long hue = 0;
  if( BUTTON_CENTRE.read() == LOW ) hue = 65536/3;
  uint32_t ACTIVE = LEDS.ColorHSV(hue, 255, 255);
  // Clear just the direction
  for( int i = 1; i <= 8; i++ ) LEDS.setPixelColor(i, BLACK);

  if( !BUTTON_DOWN.read() ) LEDS.setPixelColor(1, ACTIVE);
  if( !BUTTON_RIGHT.read() ) LEDS.setPixelColor(3, ACTIVE);
  if( !BUTTON_UP.read() ) LEDS.setPixelColor(5, ACTIVE);
  if( !BUTTON_LEFT.read() ) LEDS.setPixelColor(7, ACTIVE);

  if( !BUTTON_DOWN.read() && !BUTTON_RIGHT.read() ) LEDS.setPixelColor(2, ACTIVE);
  if( !BUTTON_RIGHT.read() && !BUTTON_UP.read() ) LEDS.setPixelColor(4, ACTIVE);
  if( !BUTTON_UP.read() && !BUTTON_LEFT.read() ) LEDS.setPixelColor(6, ACTIVE);
  if( !BUTTON_LEFT.read() && !BUTTON_DOWN.read() ) LEDS.setPixelColor(8, ACTIVE);

}

/*
 * Maps the humidity and sensor onto an LED ring connected to the LED out port
 * Temperature controls the number of LEDs, and humidity controls the hue
 * Assumes a 16 LED ring connectd to the LED out port on top of the board
 * (should probably add a switch to use the secondary LEDs as well)
 */
void temperatureToLEDRing() {
  long hue = long ((CURRENT_HUMIDITY/100) * 65535 / 3 * 2); //Use the first 2/3rds of the colour spectrum
  uint32_t ACTIVE = LEDS.ColorHSV(hue, 255, 255);
  int n_active = map( int(CURRENT_TEMP * 10 ), 18 * 10, 29 * 10, 0, 16 );
  n_active = constrain(n_active,0,16);
  for( int i = 0; i < 16; i++ ) {
    if( i < n_active ) {
      LEDS.setPixelColor(i+9, ACTIVE);
    } else {
      LEDS.setPixelColor(i+9, 0);
    }
  }
}
