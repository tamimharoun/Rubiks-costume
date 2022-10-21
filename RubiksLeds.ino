// (c) Michael Schoeffler 2017, http://www.mschoeffler.de
#include "FastLED.h"

#define DATA_PIN 3 // set the data pin on the arduino

#define BUTTON_PIN 4
#define LED_PIN 13

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS 100     // Brightness value between 0 and 255
#define LOW_BRIGHTNESS 25 // Brightness value between 0 and 255

#define NUM_LEDS 135 // 3 LEDS per square. 27 LEDs per side. 5 sides.
CRGB leds[NUM_LEDS]; // initialize an array of leds

enum Sides    {TOP,  FRONT,  RIGHT,  BACK,  LEFT,  BOTTOM}; // enum of side names
enum sColours {WHITE,  GREEN,  RED,  BLUE,  ORANGE,  YELLOW,  BLACK}; // enum of side colours

const CRGB sColour[7] = {CRGB::White, CRGB::Green, CRGB::Red, CRGB::Blue, CRGB::DarkOrange, CRGB::Yellow, CRGB::Black}; // array to store the side colours to be assigned to the leds

#define NUM_SIDES 5                              // number of sides on the cube
#define SQUARES_PER_SIDE 9                       // number of squares per side
#define NUM_SQUARES NUM_SIDES *SQUARES_PER_SIDE  // number of squares on the rubiks cube, NUM_SIDES x SQUARES_PER_SIDE
#define NUMSHUFFLES 5                            // Number of shuffles stored in the Shuffle array
#define NUMCUBESTATES 4

// Global variables
CRGB SquareColours[NUM_SQUARES] = {CRGB::Black}; // array to hold the colour of each square. initialized to all black.
unsigned int lastButtonState = 0;
unsigned int buttonState = 0; // variable for reading the pushbutton status
unsigned int cubeState = 0;
unsigned int lastCubeState = 0;
unsigned int shuffleCount = 0;
unsigned int idleLoopCount = 0;

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
   FRONT   |   RIGHT  |    BACK   |   LEFT   |  TOP   |
 46 49 52  | 109 xx 15 | 76 79 82  | 55 x  73 | 112 115 118  |
 43 40 37  | 106 xx 18 | 91 88 85  | 58 x  70 | 0 x 3  |
 28 31 34  | 103 24 21 | 94 97 100 | 61 64 67 | 6 9 12 |
******************************************/

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

// This function is called before the loop to initialize the system
void setup()
{

  delay(3000); // initial delay of a few seconds is recommended

  Serial.begin(9600);
  /*
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  */
  Serial.print("\nStarting up! \n");

  // initialize the LED pin as an output:
  pinMode(LED_PIN, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); // initializes LED strip
  FastLED.setBrightness(BRIGHTNESS); // set brightness of LEDs
  FastLED.setMaxPowerInMilliWatts(2400);

  showProgramCleanUp(1000); // turn off all LEDs
}

// Switches off all LEDs
void showProgramCleanUp(long delayTime)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(delayTime);
}

// switches on all LEDs. Each LED is shown in random color.
// numIterations: indicates how often LEDs are switched on in random colors
// delayTime: indicates for how long LEDs are switched on.
void showProgramRandom(int numIterations, long delayTime)
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

// Sets the LED at SideNum and LedNum to the colour specified. 3 Leds per square by default.
void setSquareLeds(int SideNum, int SquareNum, CRGB Colour, int NumLedsPerSquare = 3)
{
  // Convert side and square number to led number using array look-up
  int StartLed = SquareToLed[SideNum][SquareNum];

  if (StartLed < 0)
  {
    // skip this square
  }
  else
  {
    // set all the leds in the square to that colour
    for (int i = 0; i < NumLedsPerSquare; i++)
    {
      leds[StartLed + i] = Colour;
    }
  }
}

// Shows a solved rubiks cube
void showRubiksSolved(long delayTime = 100)
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

// Loop over all sides and squares and set the square colours according to the SquareColours array
void showRubiksShuffled(int choice, long delayTime = 100)
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

/*
// Loops between all the different shuffles and then shows a random shuffle at the end
void shuffleCube(long shuffleTime=500, long delayTime=5000)
{
   //loop between all the shuffles
   for (int choice = 0; choice < NUMSHUFFLES; choice++)
     {
      // show shuffle i for shuffleTime ms
      showRubiksShuffled(choice, shuffleTime);
     }
     // show a random shuffle for delayTime ms
     showRubiksShuffled(random8(), delayTime);
}
*/

// Loop over all sides and squares and set the square colours according to the SquareColours array
void testSquares(long delayTime = 500)
{
  showProgramCleanUp(500); // turn off all LEDs

  int Side, Square, i;
  // set the square leds on each side according to the chosen colour of each square
  for (Side = 0; Side < NUM_SIDES; Side++)
  {
    for (Square = 0; Square < SQUARES_PER_SIDE; Square++)
    {
      i = (Side * SQUARES_PER_SIDE) + Square; // index of square
      setSquareLeds(Side, Square, sColour[Side]);
      FastLED.show();
      delay(delayTime);
    }
  }
}

// Saves the state of the button and checks which state the button is in now
void getButtonState()
{
  lastButtonState = buttonState;
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);
  delay(10); // extra delay just in case, to make sure that we dont read the button state too often
}

// returns true if the button was pressed
bool buttonPressed()
{
  // check if the pushbutton is pressed.
  return (buttonState == HIGH && lastButtonState == LOW);
}

// returns true if the button was pressed
bool buttonReleased()
{
  // check if the pushbutton is pressed.
  return (buttonState == LOW && lastButtonState == HIGH);
}

// saves the last cube state and checks which state the cube should be in now
// 0:SHUFFLED, 1:SHUFFLING, 2:SOLVED, 3:SHUFFLING, 4: ----, 5: SLEEPING
void getCubestate()
{
  lastCubeState = cubeState;
  getButtonState(); // get the button state
  
  if (buttonPressed())
  {
    cubeState++; // go to the next state if the button is pressed
    if (cubeState >= NUMCUBESTATES) 
    {
      cubeState = 0;  // go back to the first state when the max number of states is reached
    }
  }

  // count how many times the cube stayed in the same state
  if (cubeState == lastCubeState)
  {
    idleLoopCount++;
  }
  else
  {
    idleLoopCount = 0;
  }
  // check if the cube has been idle for 1000 cycles
  if (idleLoopCount == 1000) // 1000 cycles is ~60 seconds
  {
    cubeState = 5; // go to sleeping state when idle
  }
}

// returns true if the cube state has changed
bool cubeStateChanged()
{
  return lastCubeState != cubeState;
}

void loop()
{
  delay(50); // cycle time for the loop
  getCubestate();
  switch (cubeState)
  {
  case 0: // SHUFFLED
    if (cubeStateChanged())
    {
      Serial.print("\nSHUFFLED!\n"); // Go to the shuffled state
      showRubiksShuffled(random8(), 50);
    }
    break;
  case 1: // SHUFFLING
  case 3: // SHUFFLING
    if (cubeStateChanged())
    {
      Serial.print("SHUFFLING."); // continue shuffling
    }
    Serial.print("."); // continue shuffling
    showRubiksShuffled(random8(), 100);
    break;
  case 2: // SOLVED
    if (cubeStateChanged())
    {
      Serial.print("\nSOLVED!\n"); // Go to the solved state
      showRubiksSolved(50);
    }
    break;
  case 5: // SLEEP
    if (cubeStateChanged())
    {
      showProgramCleanUp(50);
      Serial.print("Shutting off LEDs.\n");
    }
    break;
  default:
    //showProgramRandom(10,200);
    Serial.print("Oops! Cube state does not exist!");
    break;
  }

}

/*
// test program
void testloop() {

 // Remove the delays in each function
  // As long as the state is not changing, continue in the current state
  // showShuffled and showSolved are only shown at state changes
  // New function is needed to keep shuffling every X cycles (or Y ms)

  testSquares();

  showProgramCleanUp(500); // turn off all LEDs

  showRubiksSolved(5000); // show a solved cube

  //showProgramRandom(10,3000);

}
*/