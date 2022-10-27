/**
 * @file RubiksLeds.ino
 * @authors Tamim Haroun, Zaid Haroun
 * @brief Rubiks cube Haloween costume project, 2022
  */

#include "FastLED.h"    // Helper library for controlling the LEDs

#define DATA_PIN 3    // set the data pin on the arduino
#define BUTTON_PIN 4  // set the pushbutton pin on the arduino. 
                      // Connect one lead of the pushbutton and a 10k resistor to ground from this pin. 
                      // The other lead of the pushbutton should be connected to 5V.

#define LED_TYPE WS2812B    // set up the type of LED
#define COLOR_ORDER GRB     // set up the colour order
#define BRIGHTNESS 100      // Choose a brightness value between 0 and 255

#define NUM_LEDS 135      // 3 LEDS per square. 27 LEDs per side. 5 sides.
CRGB leds[NUM_LEDS];      // initialize an array of leds

enum Sides    {TOP,  FRONT,  RIGHT,  BACK,  LEFT,  BOTTOM};           // enum of side names. Added for guidance only, to indicate what colour each side is.
enum sColours {WHITE,  GREEN,  RED,  BLUE,  ORANGE,  YELLOW,  BLACK}; // enum of side colours
enum cubeStates {SLEEPING, CODE_RED, SOLVING, SOLVED, SHUFFLING, SHUFFLED};     // enum of cube states

const CRGB sColour[7] = {CRGB::White, CRGB::Green, CRGB::Red, CRGB::Blue, CRGB::DarkOrange, CRGB::Yellow, CRGB::Black}; // array to store the side colours to be assigned to the leds

#define NUM_SIDES 5                              // number of sides on the cube
#define SQUARES_PER_SIDE 9                       // number of squares per side
#define NUM_SQUARES NUM_SIDES *SQUARES_PER_SIDE  // number of squares on the rubiks cube, NUM_SIDES x SQUARES_PER_SIDE
#define NUMSHUFFLES 5                            // Number of shuffles stored in the Shuffle array
#define CYCLE_DELAY_TIME 50                      // Delay time between each loop in the main program
#define SLEEP_TIME 300000                         // Time after which the cube will go to sleep

// Global variables
CRGB SquareColours[NUM_SQUARES] = {CRGB::Black}; // array to hold the colour of each square. initialized to all black.

unsigned int buttonState = 0;       // pushbutton state
unsigned int lastButtonState = 0;   // previous pushbutton state
unsigned int cubeState = SOLVED;         // cube state
unsigned int lastCubeState = SLEEPING;     // previous cube state
unsigned long buttonPressedMillis = 0;   // button pressed time in ms
unsigned long buttonReleasedMillis = 0;  // button pressed time in ms
unsigned long stateChangeTime = 0;       // state change time in ms

// Mapping between side and square to Led number. 
// -1 is a special value which means no LEDs there.
const int SquareToLed[NUM_SIDES][SQUARES_PER_SIDE] = {
    //  1 ,  2 ,  3 ,  4 ,  5 ,  6 ,  7 ,  8 ,  9     // Square number
    {112, 115, 118, 0, -1, 3, 6, 9, 12},     // TOP
    {46, 49, 52, 43, 40, 37, 28, 31, 34}, // FRONT
    {109, -1, 15, 106, -1, 18, 103, 24, 21}, // RIGHT
    {76, 79, 82, 91, 88, 85, 94, 97, 100}, // BACK
    {55, -1, 73, 58, -1, 70, 61, 64, 67} // LEFT
};

/*********** LED Arrangement ***********
 * 1 2 3 *
 * 4 5 6 *
 * 7 8 9 *
   FRONT   |   RIGHT   |    BACK   |   LEFT   |      TOP    |
 46 49 52  | 109 xx 15 | 76 79 82  | 55 x  73 | 112 115 118 |
 43 40 37  | 106 xx 18 | 91 88 85  | 58 x  70 |   0  x   3  |
 28 31 34  | 103 24 21 | 94 97 100 | 61 64 67 |   6  9   12 |
**************************************************************/

// Two dimensional array that stores the colours for each shuffle.
const sColours Shuffle[NUMSHUFFLES][NUM_SQUARES] = {
    {GREEN, WHITE, RED, GREEN, WHITE, GREEN, ORANGE, WHITE, YELLOW,
     YELLOW, GREEN, RED, RED, GREEN, WHITE, GREEN, ORANGE, GREEN,
     GREEN, YELLOW, BLUE, BLUE, RED, ORANGE, ORANGE, RED, ORANGE,
     WHITE, RED, ORANGE, YELLOW, BLUE, BLUE, BLUE, ORANGE, RED,
     YELLOW, RED, BLUE, YELLOW, ORANGE, YELLOW, BLUE, BLUE, RED},

    {GREEN, BLUE, GREEN, YELLOW, WHITE, GREEN, YELLOW, GREEN, RED,
     GREEN, WHITE, YELLOW, ORANGE, GREEN, BLUE, GREEN, GREEN, BLUE,
     BLUE, RED, WHITE, WHITE, RED, BLUE, WHITE, YELLOW, BLUE,
     ORANGE, YELLOW, ORANGE, RED, BLUE, RED, RED, RED, ORANGE,
     YELLOW, ORANGE, RED, YELLOW, ORANGE, WHITE, YELLOW, ORANGE, RED},

    {ORANGE, RED, ORANGE, ORANGE, WHITE, ORANGE, BLUE, ORANGE, BLUE,
     YELLOW, BLUE, YELLOW, RED, GREEN, GREEN, BLUE, YELLOW, WHITE,
     ORANGE, WHITE, WHITE, ORANGE, RED, RED, GREEN, WHITE, RED,
     BLUE, WHITE, YELLOW, YELLOW, BLUE, GREEN, GREEN, WHITE, GREEN,
     GREEN, YELLOW, RED, YELLOW, ORANGE, BLUE, RED, GREEN, WHITE},

    {BLUE, ORANGE, GREEN, YELLOW, WHITE, RED, RED, BLUE, GREEN,
     GREEN, YELLOW, WHITE, BLUE, GREEN, GREEN, BLUE, RED, GREEN,
     ORANGE, WHITE, ORANGE, WHITE, RED, WHITE, RED, BLUE, YELLOW,
     YELLOW, YELLOW, WHITE, BLUE, BLUE, GREEN, BLUE, GREEN, WHITE,
     RED, RED, WHITE, ORANGE, ORANGE, RED, ORANGE, ORANGE, RED},

    {YELLOW, RED, ORANGE, RED, WHITE, WHITE, WHITE, WHITE, BLUE,
     BLUE, BLUE, ORANGE, GREEN, GREEN, ORANGE, RED, YELLOW, GREEN,
     WHITE, ORANGE, GREEN, BLUE, RED, WHITE, RED, RED, ORANGE,
     WHITE, BLUE, BLUE, GREEN, BLUE, GREEN, GREEN, YELLOW, BLUE,
     RED, WHITE, RED, ORANGE, ORANGE, YELLOW, ORANGE, YELLOW, WHITE}};

// function declarations

void switchOffLeds(long delayTime);
void showRandomLeds(int numIterations, long delayTime);
void showSolvedCube(long delayTime);
void showShuffledCube(int choice, long delayTime);
void setSquareLeds(int SideNum, int SquareNum, CRGB Colour, int NumLedsPerSquare);
void getButtonState();
void setCubeState();
bool buttonPressed();
bool buttonReleased();
bool longButtonPress();
bool cubeStateChanged();

/// @brief This function is called before the loop to initialize the system
void setup()
{

  delay(3000); // initial delay of a few seconds is recommended

  // Serial output for debugging
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("\nStarting up! \n");
  

  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); // initialize LED strip
  FastLED.setBrightness(BRIGHTNESS);      // set brightness of LEDs
  FastLED.setMaxPowerInMilliWatts(2400);  // set maximum power draw 

  switchOffLeds(1000); // turn off all LEDs
}

/// @brief Switches off all LEDs
/// @param delayTime Specifies how long to wait after sending the command to the LEDs
void switchOffLeds(long delayTime=50)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(delayTime);
}

/// @brief Switches on all LEDs with random colors
/// @param numIterations How many times to perform this operation
/// @param delayTime How long to wait after sending the command to the LEDs
void showRandomLeds(int numIterations=10, long delayTime=50)
{
  for (int iteration = 0; iteration < numIterations; ++iteration)
  {
    for (int i = 0; i < NUM_LEDS; ++i)
    {
      leds[i] = CHSV(random8(), 255, 255); // hue, saturation, value
    }
    FastLED.show();
    delay(delayTime);
  }
}

/// @brief Sets the LED at SideNum and LedNum to the colour specified. 3 Leds per square by default.
/// @param SideNum Side number (see Sides Enum)
/// @param SquareNum Square number; left to right, top to bottom.
/// @param Colour Colour of the square
/// @param NumLedsPerSquare Number of LEDs to light up per square
void setSquareLeds(int SideNum, int SquareNum, CRGB Colour, int NumLedsPerSquare = 3)
{
  // Convert side and square number to led number using look-up table
  int StartLed = SquareToLed[SideNum][SquareNum];
  
  if (StartLed >= 0)
  {
    // set all the leds in the square to that colour
    for (int i = 0; i < NumLedsPerSquare; i++)
    {
      leds[StartLed + i] = Colour;
    }
  }
  else
  {
    // skip this square
  }
}

/// @brief Shows a solved cube. Side colours specified in enum sColours.
/// @param delayTime How long to wait after sending the command to the LEDs
void showSolvedCube(long delayTime = 100)
{
  int Side, Square;
  // loop over all sides
  for (Side = 0; Side < NUM_SIDES; Side++)
  {
    // loop over all squares in a side
    for (Square = 0; Square < SQUARES_PER_SIDE; Square++)
    {
      // set the led to the 'solved colour' of that side
      setSquareLeds(Side, Square, sColour[Side]);
    }
  }
  FastLED.show(); // show the leds
  delay(delayTime);
}

/// @brief Shows a shuffled cube. Sets the square colours according to the SquareColours array
/// @param choice which pre-defined shuffle to choose
/// @param delayTime How long to wait after sending the command to the LEDs
void showShuffledCube(int choice, long delayTime = 100)
{
  int Side, Square, i;

  // divide by the number of shuffles and get the remainder, in case a non-existent shuffle was chosen
  choice = choice % NUMSHUFFLES;

  // set all the square colours according to the chosen shuffle
  for (i = 0; i < NUM_SQUARES; i++)
  {
    SquareColours[i] = sColour[Shuffle[choice][i]];
  }
  // set the square leds on each side according to the chosen colour of each square
  for (Side = 0; Side < NUM_SIDES; Side++)
  {
    for (Square = 0; Square < SQUARES_PER_SIDE; Square++)
    {
      i = (Side * SQUARES_PER_SIDE) + Square; // index of square
      setSquareLeds(Side, Square, SquareColours[i]);
    }
  }
  FastLED.show();
  delay(delayTime);
}

/// @brief Saves the last state of the button and checks the current state of the button
///        saves the time of the button press and release events
void getButtonState()
{
  lastButtonState = buttonState;            // save the state of the button
  buttonState = digitalRead(BUTTON_PIN);    // read the current state of the pushbutton
  
  if (buttonPressed())
    {
      buttonPressedMillis = millis(); // record the time of the button press event
      //Serial.print("\n pressed = ");
      //Serial.print(buttonPressedMillis);
    }

  if (buttonReleased())
    {
      buttonReleasedMillis = millis();  // record the time of the button release event
      //Serial.print("\n released = ");
      //Serial.print(buttonReleasedMillis);
    }
}

/// @brief Checks if the button was pressed
/// @return returns true if the button was pressed
inline bool buttonPressed() { return (buttonState == HIGH && lastButtonState == LOW); }

/// @brief Checks if the button was released
/// @return returns true if the button was released
inline bool buttonReleased() { return (buttonState == LOW && lastButtonState == HIGH); }

/// @brief Checks if the button was long-pressed
/// @return returns true if the button was pressed for longer than 2 seconds
inline bool longButtonPress() { return ((buttonReleasedMillis - buttonPressedMillis) > 2000); }

/// @brief Check if the cube state has changed
/// @return Returns true if the cube state has changed
inline bool cubeStateChanged() { return lastCubeState != cubeState; }

/// @brief Saves the last cube state and checks which state the cube should be in now
void setCubeState()
{
  lastCubeState = cubeState;  // save the state of the cube
  
  unsigned long currentMillis = millis();                         // current time in ms
  unsigned long buttonIdleTime = currentMillis - buttonPressedMillis;   // time since button was pressed
  unsigned long stateIdleTime = currentMillis - stateChangeTime;    // time since state was changed

  if (buttonPressed() || stateIdleTime >= 60000)
  {
    switch (cubeState)
    {
    case SOLVED:
      cubeState = SHUFFLING;
      break;
    case SHUFFLING:
      cubeState = SHUFFLED;
      break;    
    case SHUFFLED:
      cubeState = SOLVING;
      break;    
    case SOLVING:
      cubeState = SOLVED;
      break;
    case SLEEPING:
      cubeState = SOLVED;
      break;
    case CODE_RED:
      cubeState = SOLVED;
      break;
    default:
      cubeState = SOLVED;  // loop back to the first state when the max number of states is reached
    }
    stateChangeTime = millis();
  }

  // check if this was a long button press, do special action
  if (buttonReleased() && longButtonPress())
       cubeState = CODE_RED;

  if (buttonIdleTime >= SLEEP_TIME)
    cubeState = SLEEPING; // go to sleeping state if button has not been pressed for IDLE_TIME ms

}

/// @brief Main program loop.
///        Executes a cyclic check of the cube state and performs the action relevant for that state 
void loop()
{
  delay(CYCLE_DELAY_TIME); // cycle time for the loop
  getButtonState();        // get the button state
  setCubeState();          // update the cube state
  switch (cubeState)
  {
  case SLEEPING:
    if (cubeStateChanged())
    {
      switchOffLeds(50);
    }
    break;
  case SHUFFLED:
    if (cubeStateChanged())
    {
      showShuffledCube(random8(), 50);
    }
    break;
  case SHUFFLING: // Shuffling and Solving are the same
  case SOLVING:
    showShuffledCube(random8(), 100);   // show each random state for 100 ms
    break;
  case SOLVED:
    if (cubeStateChanged())
    {
      showSolvedCube(50);
    }
    break;
  case CODE_RED:
    if (cubeStateChanged())
    {
      FastLED.showColor(CRGB::Red);
      delay(50);
    }
    break;
  default:
    showRandomLeds(10,500);
    break;
  }

}