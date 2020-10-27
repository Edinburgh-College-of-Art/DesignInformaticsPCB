/*
 * Example program that tries to do everything all at once... It:
 * - shows current temperature and humidit on the screen, and on an LED ring
 * - lights up when the buttons are pressed
 * - uses the buttons to move a dot around the screen
 * - shows whether an RFID tag is present and the ID
 * - uses the joystick (or knobs) to steer a dot on the screen
 */

#include <DI.h>

int button_column = 0;
int button_row = 0;

const int GRID_SIZE = 5;
const int GRID_CIRCLE_SIZE = 6;
const int GRID_START_X = 66;
const int GRID_START_Y = 66;

word SCREEN_BACKGROUND = RGBToScreen(0,50,90);
word TEXT_COLOR = ST77XX_WHITE;

void setup() {
  // put your setup code here, to run once:
  setupEverything(true);
  showDISplash();
  delay(1000);
  SCREEN.fillRect(0,0, 128, 128, SCREEN_BACKGROUND );
}

void loop() {
  // Update all of the Inputs
  if(oneIn(50) ) updateTemperature();
  updateButtons(false);
  updateKnobs();
  
  if( oneIn(50) ) updateRFID();

  // Update internal states
  updateGridPosition();

  // Translate the Inputs to the Outputs
  buttonsToLeds();

  // Updte things on the screen
  if( oneIn(30) ) {
    drawGrid();
    drawKnobsAndPoint();
    temperatureToScreen();
    temperatureToLEDRing();
    rfidToScreen();
  }

  // Update all of the Outputs
  updateLoopCounter();
  updateWatchdogLED();
  outputLEDs();
}


/*
 * Writing the current temperature on the screen is fairly easy
 */
void temperatureToScreen() {
  SCREEN.setFont();
  SCREEN.setCursor(5, 32);
  SCREEN.setTextColor(TEXT_COLOR,SCREEN_BACKGROUND);

  SCREEN.print("Temp: ");
  SCREEN.print(CURRENT_TEMP);
  SCREEN.print("C");
  SCREEN.setCursor(5, 42);
  SCREEN.print("Humi: ");
  SCREEN.print(CURRENT_HUMIDITY);
  SCREEN.print("%\n");
}

void rfidToScreen() {
  if( RFID_PRESENT )   SCREEN.setTextColor(ST77XX_RED,SCREEN_BACKGROUND);
  else SCREEN.setTextColor(TEXT_COLOR,SCREEN_BACKGROUND);
  SCREEN.setCursor(5, 52);
  SCREEN.print("RFID: ");  
  SCREEN.print(RFID_ID);  
}

// When drawing the grid of circles on the screen, where should the dot be?
void updateGridPosition() {
  if( BUTTON_UP.fell() ) button_row--;
  if( BUTTON_DOWN.fell() ) button_row++;
  if( BUTTON_LEFT.fell() ) button_column--;
  if( BUTTON_RIGHT.fell() ) button_column++;
}

void drawGrid() {
  if( button_row < 0 ) button_row = GRID_SIZE-1;
  if( button_row >= GRID_SIZE ) button_row = 0;
  if( button_column < 0 ) button_column = GRID_SIZE-1;
  if( button_column >= GRID_SIZE ) button_column = 0;
  int start_x = GRID_START_X;
  int start_y = GRID_START_Y;
  int circ_size = GRID_CIRCLE_SIZE;

  for( int r = 0; r < GRID_SIZE; r++ )
    for( int c = 0; c < GRID_SIZE; c++ ) {
      int x_pos = start_x + 2 * c * circ_size + circ_size;
      int y_pos = start_y + 2 * r * circ_size + circ_size;
      if( button_column == c && button_row == r )
        SCREEN.fillCircle(x_pos, y_pos, circ_size, BUTTON_CENTRE.read() ? ST77XX_GREEN : ST77XX_RED );
      else {
        SCREEN.fillCircle(x_pos, y_pos, circ_size, ST77XX_BLACK);
        SCREEN.drawCircle(x_pos, y_pos, circ_size, ST77XX_GREEN);
      }
    }
}



/*
 * Sorry, graphics programmin needs lots of constants!
 */

int POINT_START_X = 0;
int POINT_START_Y = 64;
int POINT_WIDTH=64;
int POINT_HEIGHT=64;
int SLIDER_SIZE=5;
int INDICATOR_SIZE=5;
int POINT_RANGE_X = POINT_WIDTH-SLIDER_SIZE;
int POINT_RANGE_Y = POINT_HEIGHT-SLIDER_SIZE;
int point_x = POINT_RANGE_X / 2;
int point_y = POINT_RANGE_Y / 2;
word BACKGROUND_COLOR = RGBToScreen(50,50,50);
int X_OFFSET = POINT_START_X + SLIDER_SIZE;
int Y_OFFSET = POINT_START_Y + SLIDER_SIZE;

void drawKnobsAndPoint() {
  if(FIRST) {
    SCREEN.fillRect(POINT_START_X + INDICATOR_SIZE, POINT_START_Y + INDICATOR_SIZE, POINT_RANGE_X, POINT_RANGE_Y, BACKGROUND_COLOR );
  }
  SCREEN.fillCircle(X_OFFSET+point_x,Y_OFFSET+point_y,3, BACKGROUND_COLOR );
  int dx = -((JOYSTICK_X / 200 ) - 2);
  int dy = ((JOYSTICK_Y / 200 ) - 2 );
  int point_size = 58;
  point_x = ((point_x + dx) + POINT_RANGE_X )% POINT_RANGE_X;
  point_y = ((point_y + dy) + POINT_RANGE_Y )% POINT_RANGE_Y;
  //tft.drawRect(0,64,point_size,point_size, ST77XX_BLACK);
  SCREEN.fillCircle(X_OFFSET+point_x,Y_OFFSET+point_y,3, ST77XX_YELLOW );
  

  SCREEN.fillRect(POINT_START_X+SLIDER_SIZE,POINT_START_Y,POINT_WIDTH-SLIDER_SIZE,SLIDER_SIZE, ST77XX_YELLOW );
  int x_pos = map(JOYSTICK_X,1024,0,POINT_START_X + SLIDER_SIZE, POINT_START_X + POINT_WIDTH - INDICATOR_SIZE);
  SCREEN.fillRect(x_pos,POINT_START_Y,INDICATOR_SIZE,SLIDER_SIZE, ST77XX_RED );
  
  SCREEN.fillRect(POINT_START_X,POINT_START_Y+SLIDER_SIZE,SLIDER_SIZE, POINT_HEIGHT-SLIDER_SIZE,ST77XX_YELLOW );
  int y_pos = map(JOYSTICK_Y,0,1024,POINT_START_Y + SLIDER_SIZE, POINT_START_Y + POINT_HEIGHT - INDICATOR_SIZE);
  SCREEN.fillRect(POINT_START_X,y_pos,SLIDER_SIZE,INDICATOR_SIZE, ST77XX_RED );

}
