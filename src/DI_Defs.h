
#ifndef DI_DEFS
#define DI_DEFS

#define BUT_UP  1
#define BUT_LEFT  17
#define BUT_CENT 20
#define BUT_RIGHT  0
#define BUT_DOWN  4

// LED Setup
#define INTERNAL_LED_PIN    21
#define INTERNAL_LED_COUNT 9
#define INTERNAL_LED_WITH_RING_COUNT 25
#define EXTERNAL_LED_PIN  6



//TEMPERATURE
#define TEMPERATURE_PIN 2
// Uncomment the type of sensor in use:
#define TEMPERATURE_TYPE    DHT11     // DHT 11

// SCREEN
#define TFT_CS        8
#define TFT_RST        0 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC        9

// Joystick
#define JOYSTICK_X_PIN  A0 //A2
#define JOYSTICK_Y_PIN  A1 //A3
#define KNOB_1_PIN  A1 //A2
#define KNOB_2_PIN  A0 //A3

// RFID
#define RFID_RST_PIN         0          // Configurable, see typical pin layout above
#define RFID_SS_PIN          10         // Configurable, see typical pin layout above


#define SERVO_1 3
#define SERVO_2 5
#endif
